#include <vector>

class Point {
  public:
    int key;
    std::vector<double> coordinates;

    Point(std::vector<double> coordinates, int key);
    ~Point();

    // Calculates distance of point to other point using Euclidean distance
    double distanceTo(std::vector<double> coordinates);
    int dimensions();
};