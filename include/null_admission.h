// Copyright 2018, Oath Inc.
// Licensed under the terms of the Apache 2.0 open source license
// See LICENSE file for terms.
/* 
 * Null admission policy
 *
 */

#ifndef NULL_ADMISSION_H_
#define NULL_ADMISSION_H_

#include "cache_policy.h"

class NullAdmission : public CacheAdmission {

    public:
        NullAdmission();
        ~NullAdmission();

        bool check(std::string key, item_packet* ip_inst);
        float get_fill_percentage();

        // Reporting
        void periodic_output(unsigned long ts, std::ostringstream& outlogfile);
};


#endif /* NULL_ADMISSION_H__ */
