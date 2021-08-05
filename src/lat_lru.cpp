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

using namespace std;
/*
 * Main!
 *
 */
int main(int argc, char *argv[]) {

    cout << "\nExecutable: \t" << argv[0] << "\n";

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

    // Let's make a hard drive
    Cache* hd = new Cache(0, false, false, hd_max_size_gig, 0, 0);
    CacheAdmission* hd_ad = new LatencyAdmission(25, 75);
    //CacheAdmission* hd_ad = new NullAdmission();
    CacheEviction* hd_evict = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    hd->set_admission(hd_ad);
    hd->set_eviction(hd_evict);

    /* Config the cache layers we made */
    // TODO: KC disabled!
    //em->add_to_tail(kc);
    em->add_to_tail(hd);

    // Run it
    /**************************/
    em->populate_access_log_cache();
    /**************************/

    delete hd;
    delete hd_ad;
    delete hd_evict;

    delete em;

    return 0;
}
