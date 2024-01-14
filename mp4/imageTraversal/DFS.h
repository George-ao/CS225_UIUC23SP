#ifndef DFS_H
#define DFS_H

#include <iterator>
#include <cmath>
#include <list>
#include <stack>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace cs225;
//added 
#include<iostream>
#include<stack>
using namespace std;
/**
 * A depth-first ImageTraversal.
 */
class DFS : public ImageTraversal {
public:
  DFS(const PNG & png, const Point & start, double tolerance);
  
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
  stack<Point> stack_;
  //list<Point> traversal_list; 


};

#endif
