#include <iostream>
#include <fstream>
#include <sstream>

// Emulator stuff we will always need
#include "em_structs.h"
#include "emulator.h"
#include "cache.h"

// The specific policies we will consider
#include "second_hit_admission.h"
#include "null_admission.h"
#include "lru_eviction.h"
#include "fifo_eviction.h"

using namespace std;
/*
 * Boston, LA, and Richmond with 2hc and lru.
 *
 */
int main(int argc, char *argv[]) {

    cout << "\nExecutable: \t" << argv[0] << "\n";
    cout << "Server 0 in Boston, MA\n";
	  cout << "Server 1 in LA, CA\n";
    cout << "Server 2 in Richmond, VA\n";

    Emulator* em = new Emulator(cout, false, argc, argv);


    // Some random seeding work
    srand(time(NULL));
    ostringstream ossf;
    ossf << rand();

    // Some reused parameters

    unsigned long long hd_max_size_gig = em->sci->hd_gig;
    unsigned long long hd_max_size_bytes = hd_max_size_gig *1024*1024*1024;

    string hd_file_name = string(ossf.str() + ".bf");

    Cache* boston = new Cache(0, false, false, hd_max_size_gig, 42.3601, 71.0589);
    Cache* la = new Cache(0, false, false, hd_max_size_gig, 34.0522, 118.2437);
    Cache* richmond = new Cache(0, false, false, hd_max_size_gig, 37.5407, 77.4360);
    
    CacheAdmission* ad1 = new SecondHitAdmissionRot(hd_file_name, 5,
                                                   50*1024*1024*8,
                                                   em->sci->_NVAL,//2nd hit
                                                   em->sci->no_bf_cust,
                                                   em->sci->bf_reset_int);
    CacheEviction* evict1 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    boston->set_admission(ad1);
    boston->set_eviction(evict1);

    CacheAdmission* ad2 = new SecondHitAdmissionRot(hd_file_name, 5,
                                                   50*1024*1024*8,
                                                   em->sci->_NVAL,//2nd hit
                                                   em->sci->no_bf_cust,
                                                   em->sci->bf_reset_int);
    CacheEviction* evict2 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    la->set_admission(ad2);
    la->set_eviction(evict2);

    CacheAdmission* ad3 = new SecondHitAdmissionRot(hd_file_name, 5,
                                                   50*1024*1024*8,
                                                   em->sci->_NVAL,//2nd hit
                                                   em->sci->no_bf_cust,
                                                   em->sci->bf_reset_int);
    CacheEviction* evict3 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    richmond->set_admission(ad3);
    richmond->set_eviction(evict3);

    /* Config the cache layers we made */

    em->add_to_tail(boston, "Boston, MA");
	  em->add_to_tail(la, "Los Angeles, CA");
    em->add_to_tail(richmond, "Richmond, VA");
    // Run it
    /**************************/
    em->populate_access_log_cache();
    /**************************/

    delete boston;
    delete la;
    delete richmond;

    delete ad1;
    delete evict1;
    delete ad2;
    delete evict2;
    delete ad3;
    delete evict3;

    delete em;

    return 0;
}
