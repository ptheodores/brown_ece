#include <iostream>
#include <fstream>
#include <sstream>

// Emulator stuff we will always need
#include "em_structs.h"
#include "emulator.h"
#include "cache.h"

// The specific policies we will consider
#include "latency_admission.h"
#include "null_admission.h"
#include "lru_eviction.h"
#include "fifo_eviction.h"
#include "lat_dis_admission.h"


using namespace std;
/*
 * Main!
 *
 */
int main(int argc, char *argv[]) {

    cout << "\nExecutable: \t" << argv[0] << "\n";
    cout << "Server 0 in Boston" << "\n";
	cout << "Server 1 in LA" << "\n";

    Emulator* em = new Emulator(cout, false, argc, argv);


    // Some random seeding work
    srand(time(NULL));
    ostringstream ossf;
    ossf << rand();

    // Some reused parameters

    unsigned long long hd_max_size_gig = em->sci->hd_gig;
    unsigned long long hd_max_size_bytes = hd_max_size_gig *1024*1024*1024;

    string kc_file_name = string(ossf.str() + ".kcbf");
    string hd_file_name = string(ossf.str() + ".bf");

    Cache* boston = new Cache(0, false, false, hd_max_size_gig, 42.3601, 71.0589);
    Cache* louisville = new Cache(0, false, false, hd_max_size_gig, 38.2527, 85.7585);
    
    CacheAdmission* boston_ad = new DistanceAdmission(12000, 15000, 42.3601, 71.0589);
    //CacheAdmission* hd_ad = new NullAdmission();
    CacheEviction* hd_evict = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    boston->set_admission(boston_ad);
    boston->set_eviction(hd_evict);

    CacheAdmission* louisville_ad = new DistanceAdmission(10000, 14000, 38.2527, 85.7585);
    //CacheAdmission* hd_ad = new NullAdmission();
    CacheEviction* evict = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    louisville->set_admission(louisville_ad);
    louisville->set_eviction(evict);

    /* Config the cache layers we made */

    em->add_to_tail(boston);
	em->add_to_tail(louisville);
    // Run it
    /**************************/
    em->populate_access_log_cache();
    /**************************/

    delete boston;
    delete louisville;

    delete boston_ad;
    delete louisville_ad;
    delete hd_evict;

    delete em;

    return 0;
}
