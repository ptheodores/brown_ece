/*
 * Latency-Aware Cache Admission Policy That Uses Distance (not rtt)
 *
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <string>
#include <sstream>
#include "cache_policy.h"
#include "lat_dis_admission.h"
#include "distance.h"

using namespace std;

DistanceAdmission::DistanceAdmission(long double min, long double max, long double latitude, long double longitude) {
    name = "distance";
    this->lower = lower;
    this->upper = upper;
    this->latitude = latitude;
    this->longitude = longitude;
}

DistanceAdmission::~DistanceAdmission() {
}

bool DistanceAdmission::check(string key, item_packet* ip_inst) {
    // admit item if and only if the latency is within bounds
    // if latency is low, will be too fast to care
    // if latency is high, will be too fast to care
    // time_t now = time(NULL);
    //double latency = (double) ip_inst->rtt;

    //verbose: print latency at each check
    //cerr << "latency: " << ip_inst->rtt << "\n";
    long double dis = distance(this->latitude, this->longitude, ip_inst->latitude, ip_inst->longitude);
    return dis <= this->upper && dis >= this->lower;
}

float DistanceAdmission::get_fill_percentage() {
    return 0;
}

void DistanceAdmission::periodic_output(unsigned long ts, std::ostringstream& outlogfile){
    // Just output the marker and move on
    //not sure we are doing anything with this right now, but we have it as an option to use?
    //outlogfile << " : " << name << " ";
}


