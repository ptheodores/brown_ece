#include <vector>
#include "distance.h"

// Authored by Edward Xing 6/25/2021

class Point {
  public:
    int key;
    std::vector<double> coordinates;

    Point(std::vector<double> coordinates, int key);
    ~Point();

    // Calculates distance of point to other point using Euclidean distance
    double distanceTo(std::vector<double> coordinates, bool haversine=false);
    int dimensions();
};