#ifndef BFS_H
#define BFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
//added 
#include<iostream>
#include<queue>
using namespace std;

using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 */
class BFS : public ImageTraversal {
public:
  BFS(const PNG & png, const Point & start, double tolerance);

  ImageTraversal::Iterator begin();
  ImageTraversal::Iterator end();
  
  void add(const Point & point);
  Point pop();
  Point peek() const;
  bool empty() const;

private:
  //private variables that are needed
  PNG png_;
  Point start_;
  double tolerance_;
  //list<Point> visited_list;
  //list<bool> visited_check;
  // vector<vector<bool>> visited_check; //(false,vector<bool> (false));
  queue<Point> queue_;
  // list<Point> traversal_list; 
};

#endif
