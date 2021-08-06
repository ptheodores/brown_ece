/* 
 * Latency-Aware admission policy
 *
 */

#ifndef DISTANCE_ADMISSION_H_
#define DISTANCE_ADMISSION_H_

#include "cache_policy.h"

class DistanceAdmission : public CacheAdmission {

    public:
        DistanceAdmission(long double lower, long double upper, 
        	long double latitude, long double longitude);
        ~DistanceAdmission();

        bool check(std::string key, item_packet* ip_inst);
        float get_fill_percentage();

        // Reporting
        void periodic_output(unsigned long ts, std::ostringstream& outlogfile);

    private:
        long double lower;
        long double upper;
        long double latitude;
        long double longitude;
};


#endif
