/*
 * Latency-Aware Cache Admission Policy
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
#include "latency_admission.h"

using namespace std;

LatencyAdmission::LatencyAdmission(double lower, double upper) {
    name = "latency";
    this->lower = lower;
    this->upper = upper;
}

LatencyAdmission::~LatencyAdmission() {
}

bool LatencyAdmission::check(string key, item_packet* ip_inst) {
    // admit item if and only if the latency is within bounds
    // if latency is low, will be too fast to care
    // if latency is high, will be too fast to care
    // time_t now = time(NULL);
    //double latency = (double) ip_inst->rtt;

    //verbose: print latency at each check
    //cerr << "latency: " << ip_inst->rtt << "\n";
    return ip_inst->rtt <= this->upper && ip_inst->rtt >= this->lower;
}

float LatencyAdmission::get_fill_percentage() {
    return 0;
}

void LatencyAdmission::periodic_output(unsigned long ts, std::ostringstream& outlogfile){
    // Just output the marker and move on
    //not sure we are doing anything with this right now, but we have it as an option to use?
    outlogfile << " : " << name << " ";
}

/***************************************************************/

/* Prob. Size Based Admission */
ProbLatencyAdmission::ProbLatencyAdmission(unsigned long long c) {
    name = "prob_lat";
    this->c = c;
}

ProbLatencyAdmission::~ProbLatencyAdmission() {
}

// Should we let this in?
bool ProbLatencyAdmission::check(string key, item_packet* ip_inst) {

    // First we need to change the type of the size

    double d_size = (double) ip_inst->size;

    // Compute the probability of admission
    double prob = 0.0;
    double r = 0.0;

    prob = 1.0 / exp( d_size / (double)c);

    // Flip a coin check the number
    r = ((double) rand() / (RAND_MAX));

    if (r < prob) {
        return true;
    }

    return false;
}

float ProbLatencyAdmission::get_fill_percentage() {
    return 0;
}

void ProbLatencyAdmission::periodic_output(unsigned long ts, std::ostringstream& outlogfile){
    // Just output the marker and move on
    outlogfile << " : " << name << " ";
}
