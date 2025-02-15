#include "kdtree.h"
#include <functional>
#include <assert.h>
#include <algorithm>

// Authored by Edward Xing 6/25/2021

using namespace std;

KDTree::Node::Node(Point *val, Node *left, Node *right) {
  this->value = val;
  this->left = left;
  this->right = right;
}

KDTree::Node::~Node() {
  delete this->value;
};

KDTree::KDTree(vector<Point*>& data, int k) {
  this->dimensions = k;
  this->size_ = data.size();
  this->root = this->build(data, k, 0);
}

KDTree::~KDTree() {
  destruct(this->root);
}

void KDTree::destruct(Node* cur) {
  if (!cur) return;
  destruct(cur->left);
  destruct(cur->right);
  delete cur;
}

int KDTree::size() {
  return this->size_;
}

vector<Point*> KDTree::knn(unsigned int k, vector<double> origin, bool haversine) {
  priority_queue<pair<double, Point*>> pq;
  this->neighbor(k, origin, this->root, pq, haversine);
  vector<Point*> ret(pq.size());
  
  int i = pq.size() - 1;
  while (!pq.empty()) {
    ret[i--] = pq.top().second;
    pq.pop();
  }
  return ret;
}

vector<Point*> subvector(int start, int end, vector<Point*> v) {
  vector<Point*> ret;
  for (int i = start; i < end; i++) {
    ret.push_back(v[i]);
  }
  return ret;
}

KDTree::Node* KDTree::build(vector<Point*>& data, int dim, int depth) {
  if (data.empty()) {
    return nullptr;
  }
  int d = depth % dim;
  int mid = data.size() / 2;

  auto comp = [&](Point *p1, Point *p2) -> bool {
    return p1->coordinates[d] < p2->coordinates[d];
  };

  nth_element(data.begin(), data.begin() + mid, data.end(), comp);
  vector<Point*> lsub = subvector(0, mid, data);
  vector<Point*> rsub = subvector(mid + 1, data.size(), data);
  Node* left = build(lsub, dim, d + 1);
  Node* right = build(rsub, dim, d + 1);
  return new Node(data[mid], left, right);
}

void KDTree::neighbor(unsigned int k, vector<double> origin, 
  Node* cur, priority_queue<pair<double, Point*>>& pq, bool haversine) {
    if (!cur || !k) return;

    int d = cur->depth % this->dimensions;
    Point* p = cur->value;
    double dist = p->distanceTo(origin, haversine);

    if (pq.size() < k) {
      pq.push(make_pair(dist, p));
    } else if (dist < pq.top().first) {
      pq.pop();
      pq.push(make_pair(dist, p));
    }

    Node *go, *other;

    if (origin[d] > p->coordinates[d]) {
      go = cur->right;
      other = cur->left;
    } else {
      go = cur-> left;
      other = cur->right;
    }
    this->neighbor(k, origin, go, pq, haversine);

    double axisDistance = origin[d] - p->coordinates[d];
    if (!pq.empty() && axisDistance <= pq.top().first) {
      this->neighbor(k, origin, other, pq, haversine);
    }
  }
