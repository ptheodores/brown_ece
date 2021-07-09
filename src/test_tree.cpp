#include "kdtree.h"
#include <iostream>

using namespace std;

int main() {
  vector<Point*> v;
  for (double i = 0.0; i < 10.0; i++) {
    v.push_back(new Point({i, i, i}, i));
  }
  KDTree* kd = new KDTree(v, 3);
  vector<Point*> ret = kd->knn(11, {0, 0, 0});
  for (Point *p : ret) {
    cout << p->key << "\n";
  }
  delete kd;

  return 0;
}