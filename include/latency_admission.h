/* 
 * Latency-Aware admission policy
 *
 */

#ifndef LATENCY_ADMISSION_H_
#define LATENCY_ADMISSION_H_

#include "cache_policy.h"

class LatencyAdmission : public CacheAdmission {

    public:
        LatencyAdmission(double lower, double upper);
        ~LatencyAdmission();

        bool check(std::string key, item_packet* ip_inst);
        float get_fill_percentage();

        // Reporting
        void periodic_output(unsigned long ts, std::ostringstream& outlogfile);

    private:
        double lower;
        double upper;
};


#endif
