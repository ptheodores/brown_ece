#include "kdtree.h"
#include <iostream>

using namespace std;

void print(vector<Point*> v) {
  for (auto p : v) {
    cout << p->key << "\n";
  }
}

int main() {
  int passed = 0;
  int failed = 0;

  vector<Point*> vec;
  for (int i = 0; i < 10; i++) {
    double c = i;
    vec.push_back(new Point({c, c}, i));
  }

  // copy vec for testing since KDTree constructor will manipulate list
  vector<Point*> v(vec);
  KDTree* kd = new KDTree(vec, 2);

  vector<Point*> t1 = kd->knn(11, {0, 0});
  if (t1 == v && t1.size() == 10 && kd->size() == 10) {
    passed++;
  } else {
    cout << "Case 1 failed!\n";
    failed++;
  }

  vector<Point*> t2 = kd->knn(2, {0, 0});
  vector<Point*> e2(v.begin(), v.begin() + 2);
  if (t2 == e2) {
    passed++;
  } else {
    cout << "Case 2 failed!\n";
    failed++;
  }

  vector<Point*> t3 = kd->knn(0, {0, 0});
  vector<Point*> e3;
  if (t3 == e3) {
    passed++;
  } else {
    cout << "Case 3 failed!\n";
    failed++;
  }

  vector<int> t4;
  for (auto& p : kd->knn(3, {5, 5})) {
    t4.push_back(p->key);
  }
  vector<int> e4 {5, 4, 6};
  if (t4 == e4) {
    passed++;
  } else {
    cout << "Case 4 failed!\n";
    failed++;
  }

  vector<Point*> t5;
  if (t5 == kd->knn(0, {3, 3})) {
    passed++;
  } else {
    cout << "Case 5 failed!\n";
    failed++;
  }

  // in tie cases knn is stable
  vector<int> t6;
  for (auto& p : kd->knn(3, {3, 5})) {
    t6.push_back(p->key);
  }
  
  if (t6[0] == 4) {
    passed++;
  } else {
    cout << "Case 6 failed!\n";
    failed++;
  }

  v.clear();
  KDTree* kd2 = new KDTree(v, 2);
  if (t5 == kd2->knn(3, {3, 5}) && kd2->size() == 0) {
    passed++;
  } else {
    cout << "Case 7 failed!\n";
    failed++;
  }

  if (failed == 0) {
    cout << "All tests passed!\n";
  } else {
    cout << passed << "/" << passed + failed << " cases passed!\n";
  }

  delete kd;
  delete kd2;

  return 0;
}