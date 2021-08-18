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
	cout << "Server 3 in Richmond" << "\n";
	cout << "Server 4 in New York City" << "\n";
	cout << "Server 5 in Houston" << "\n";
	cout << "Server 6 in Tampa" << "\n";
	cout << "Server 7 in Washington DC" << "\n";
	cout << "Server 8 in Atlanta" << "\n";
	cout << "Server 9 in Ann Arbor" << "\n";
	cout << "Server 10 in Trenton" << "\n";


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
	Cache* new_york = new Cache(0, false, false, hd_max_size_gig, 40.7128, 74.0060);
	Cache* houston = new Cache(0, false, false, hd_max_size_gig, 29.7604, 95.3698);
	Cache* tampa = new Cache(0, false, false, hd_max_size_gig, 27.9506, 82.4572);
	Cache* dc = new Cache(0, false, false, hd_max_size_gig, 38.9072, 77.0369);
	Cache* atlanta = new Cache(0, false, false, hd_max_size_gig, 33.7490, 84.3880);
	Cache* ann_arbor = new Cache(0, false, false, hd_max_size_gig, 42.2808, 83.7430);
	Cache* trenton = new Cache(0, false, false, hd_max_size_gig, 40.2206, 74.7597);
    
    CacheAdmission* boston_ad = new DistanceAdmission(750, 5000, 42.3601, 71.0589);
    CacheEviction* evict1 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    boston->set_admission(boston_ad);
    boston->set_eviction(evict1);

    CacheAdmission* louisville_ad = new DistanceAdmission(10000, 14000, 38.2527, 85.7585);
    CacheEviction* evict2 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    louisville->set_admission(louisville_ad);
    louisville->set_eviction(evict2);

    CacheAdmission* richmond_ad = new DistanceAdmission(10000, 14000, 37.5407, 77.4360);
    CacheEviction* evict3 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    richmond->set_admission(richmond_ad);
    richmond->set_eviction(evict3);

	CacheAdmission* new_york_ad = new DistanceAdmission(500, 11000, 40.7128, 74.0060);
    CacheEviction* evict4 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    new_york->set_admission(new_york_ad);
    new_york->set_eviction(evict4);

	CacheAdmission* houston_ad = new DistanceAdmission(500, 11000, 29.7604, 95.3698);
    CacheEviction* evict5 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    houston->set_admission(houston_ad);
    houston->set_eviction(evict5);

	CacheAdmission* tampa_ad = new DistanceAdmission(500, 11000, 27.9506, 82.4572);
    CacheEviction* evict6 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    tampa->set_admission(tampa_ad);
    tampa->set_eviction(evict6);

	CacheAdmission* dc_ad = new DistanceAdmission(500, 11000, 38.9072, 77.0369);
    CacheEviction* evict7 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    dc->set_admission(dc_ad);
    dc->set_eviction(evict7);

	CacheAdmission* atlanta_ad = new DistanceAdmission(500, 11000, 33.7490, 84.3880);
    CacheEviction* evict8 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    atlanta->set_admission(atlanta_ad);
    atlanta->set_eviction(evict8);

	CacheAdmission* ann_arbor_ad = new DistanceAdmission(500, 11000, 42.2808, 83.7430);
    CacheEviction* evict9 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    ann_arbor->set_admission(ann_arbor_ad);
    ann_arbor->set_eviction(evict9);

	CacheAdmission* trenton_ad = new DistanceAdmission(500, 11000, 40.2206, 74.7597);
    CacheEviction* evict10 = new LRUEviction(hd_max_size_bytes, "h", em->sci);
    trenton->set_admission(trenton_ad);
    trenton->set_eviction(evict10);

    /* Config the cache layers we made */

    em->add_to_tail(boston, "Boston, MA");
	em->add_to_tail(louisville, "Louisville, KY");
	em->add_to_tail(richmond, "Richmond, VA");
	em->add_to_tail(new_york, "New York, NY");
	em->add_to_tail(houston, "Houston, TX");
	em->add_to_tail(tampa, "Tampa, FL");
	em->add_to_tail(dc, "Washington, DC");
	em->add_to_tail(atlanta, "Atlanta, GA");
	em->add_to_tail(ann_arbor, "Ann Arbor, MI");
	em->add_to_tail(trenton, "Trenton, NJ");

    // Run it
    /**************************/
    em->populate_access_log_cache();
    /**************************/

    delete boston;
    delete louisville;
    delete richmond;
	delete new_york;
	delete houston;
	delete tampa;
	delete dc;
	delete atlanta;
	delete ann_arbor;
	delete trenton;

    delete boston_ad;
    delete evict1;
    delete louisville_ad;
    delete evict2;
    delete richmond_ad;
    delete evict3;
    delete new_york_ad;
    delete evict4;
    delete houston_ad;
    delete evict5;
    delete tampa_ad;
    delete evict6;
    delete dc_ad;
    delete evict7;
    delete atlanta_ad;
    delete evict8;
    delete ann_arbor_ad;
    delete evict9;
    delete trenton_ad;
    delete evict10;

    delete em;

    return 0;
}
