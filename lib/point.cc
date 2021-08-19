//
// Created by Edward Xing on 6/24/21.
//

#include "point.h"
#include <cmath>
#include <assert.h>
#include "distance.h"


// Authored by Edward Xing 6/25/2021

using namespace std;

Point::Point(vector<double> coordinates, int key) {
    this->coordinates = coordinates;
    this->key = key;
}

Point::~Point() {
    this->coordinates.clear();
}

double Point::distanceTo(vector<double> coordinates) {
    //double sum = 0;
    //assert(coordinates.size() == this->coordinates.size());
    //for (unsigned int i = 0; i < coordinates.size(); i++) {
    //    sum += pow(coordinates[i] - this->coordinates[i], 2);
    //}
    //return sqrt(sum);
    return distance(coordinates[1], coordinates[0], 
    	this->coordinates[1], this->coordinates[0]);
}

int Point::dimensions() {
    return this->coordinates.size();
}
