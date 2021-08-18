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
#include "second_hit_admission.h"


using namespace std;
/*
 * Main!
 *
 */
int main(int argc, char *argv[]) {

    cout << "\nExecutable: \t" << argv[0] << "\n";
    cout << "Server 1 in Boston" << "\n";
	cout << "Server 2 in Louisville" << "\n";
	cout << "Server 3 in Houston" << "\n";

    Emulator* em = new Emulator(cout, false, argc, argv);


    // Some random seeding work
    srand(time(NULL));
    ostringstream ossf;
    ossf << rand();

    // Some reused parameters

    unsigned long long hd_max_size_gig = em->sci->hd_gig;
    unsigned long long hd_max_size_bytes = hd_max_size_gig *1024*1024*1024;

    //string kc_file_name = string(ossf.str() + ".kcbf");
    string hd_file_name = string(ossf.str() + ".bf");

    Cache* boston = new Cache(0, false, false, hd_max_size_gig, 42.3601, 71.0589);
    Cache* louisville = new Cache(0, false, false, hd_max_size_gig, 38.2527, 85.7585);
	Cache* richmond = new Cache(0, false, false, hd_max_size_gig, 37.5407, 77.4360);

    
    CacheAdmission* boston_ad = new DistanceAdmission(12000, 15000, 42.3601, 71.0589);
    CacheEviction* evict1 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    boston->set_admission(boston_ad);
    boston->set_eviction(evict1);

    CacheAdmission* louisville_ad = new DistanceAdmission(10000, 14000, 38.2527, 85.7585);
    CacheEviction* evict2 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    louisville->set_admission(louisville_ad);
    louisville->set_eviction(evict2);

	/*CacheAdmission* richmond_ad = new DistanceAdmission(10000, 14000, 37.5407, 77.4360);
	CacheEviction* evict3 = new LRUEviction(hd_max_size_bytes, "h", em->sci); 
    louisville->set_admission(richmond_ad);
    louisville->set_eviction(evict3);*/

	/*CacheAdmission* richmond_ad = new SecondHitAdmissionRot(hd_file_name, 5,
                                                   50*1024*1024*8,
                                                   em->sci->_NVAL,//2nd hit
                                                   em->sci->no_bf_cust,
                                                   em->sci->bf_reset_int);*/
    CacheAdmission* richmond_ad = new DistanceAdmission(10000, 14000, 37.5407, 77.4360);
    CacheEviction* evict3 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    richmond->set_admission(richmond_ad);
    richmond->set_eviction(evict3);

    /* Config the cache layers we made */

    em->add_to_tail(boston, "Boston, MA");
	em->add_to_tail(louisville, "Louisville, KY");
	em->add_to_tail(richmond, "Richmond, VA");
    // Run it
    /**************************/
    em->populate_access_log_cache();
    /**************************/

    delete boston;
    delete louisville;
    delete richmond;

    delete boston_ad;
    delete evict1;
    delete louisville_ad;
    delete evict2;
    delete richmond_ad;
    delete evict3;

    delete em;

    return 0;
}
