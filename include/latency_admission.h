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

        bool check(std::string key, unsigned long data, unsigned long long size,
                   unsigned long ts, std::string customer_id_str);
        float get_fill_percentage();

        // Reporting
        void periodic_output(unsigned long ts, std::ostringstream& outlogfile);

    private:
        double lower;
        double upper;
};


#endif