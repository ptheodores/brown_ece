#include "point.h"
#include <queue>
#include "uthash.h"

// Authored by Edward Xing 6/25/2021

using namespace std;

class KDTree {

  class Node {
    public:
      Point *value;
      int depth;
      Node *left;
      Node *right;

      Node(Point *val, Node *left, Node *right);
      ~Node();
  };

  private:
    Node *root;
    int dimensions;
    int size_;
    
    Node* build(vector<Point*>& data, int dim, int depth);
    void neighbor(unsigned int k, vector<double> origin, 
      Node* cur, priority_queue<pair<double, Point*>>& pq);
    void destruct(Node* cur);

  public:
    KDTree(vector<Point*>& data, int k);
    ~KDTree();
    int size();
    vector<Point*> knn(unsigned int k, vector<double> origin);
};
