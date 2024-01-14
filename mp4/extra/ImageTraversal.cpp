#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 * 
 * @param p1 First pixel
 * @param p2 Second pixel
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );    
}

/**
 * check whether a point should be visited
 * 
 * @param to_judege point to judge: out of bound? out of tolerence? visited? 
 */
bool ImageTraversal::Iterator::judge_add(Point to_judge)
{
  int width = png_traversal_.width(); 
  int height = png_traversal_.height();
  int x_ = to_judge.x;
  int y_ = to_judge.y;
  //check out of png's bound first
  if(x_>=width || y_>=height) return false;
  if(x_<0 || y_<0) return false;
  //check out of tolerence then
    //get two pixerl and compare
  png_traversal_.getPixel(start_point_.x,start_point_.y); 
  png_traversal_.getPixel(x_,y_);
  double real_dist =  calculateDelta(*png_traversal_.getPixel(start_point_.x,start_point_.y),
    *png_traversal_.getPixel(x_,y_));
    //compare
  if(real_dist>=tolerence_) return false;
  //check visited
  if(visited_check[x_][y_]==true) return false;
  return true;  
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() 
{
  /** @todo [Part 1] */

  //initialize the traversal
  traversal_ = NULL;
}

/**
 * Iterator constructor.
 */
ImageTraversal::Iterator::Iterator(PNG base,Point cur_point,double tolerence,ImageTraversal* traversal )
{
  /** @todo [Part 1] */
  //renew some value 
  traversal_ = traversal;
  png_traversal_ = base;
  start_point_=cur_point;
  cur_point_=cur_point;
  tolerence_=tolerence;
  //initialize the visited_check
    int width = png_traversal_.width(); 
    int height = png_traversal_.height();
    vector<bool> temp(height);
    visited_check.resize(width,temp);
    for(int i=0; i<width;i++)
    {
      for(int j=0; j<height;j++)
      {
        visited_check[i][j]= false;
      }
    }
  //renew if visited
  if(judge_add(cur_point_)==true)
  {
    visited_check[cur_point_.x][cur_point_.y] = true;
  }
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  if(traversal_==NULL) return *this;
  //pop current first
  // traversal_->pop();
    //if empty now, the traversal end
  // if(traversal_->empty()) 
  // {
  //   traversal_=NULL;
  //   return *this;
  // }
  //add the neighbor four point
  unsigned x_ = cur_point_.x;
  unsigned y_ = cur_point_.y;

  //set to visited
  visited_check[x_][y_] = true;

  Point right(x_+1,y_);
  Point down(x_,y_+1);
  Point left(x_-1,y_);
  Point up(x_,y_-1);
    //judge
  if(judge_add(right)) traversal_->add(right);
  if(judge_add(down)) traversal_->add(down);
  if(judge_add(left)) traversal_->add(left);
  if(judge_add(up)) traversal_->add(up);

  
  //if the traversal is in progress, then we just return possible point 
  while(traversal_->empty() == false && judge_add(traversal_->peek())==false)
  {
    //pop out the visited
    traversal_->pop();

  }
    //if the traversal is finished, we get lots of point on stack/queue. But they are all visited,
    //we may need to pop them out and return when the container is empty
    if(traversal_->empty()) 
    {
      //set to null
      traversal_ = NULL;
      return *this;
    }
    //if peek is next pixer to traverse
    if(judge_add(traversal_->peek())==true)
    {
      cur_point_ = traversal_->peek();
      return *this;
    }


  return *this;
}

/**
 * Iterator accessor opreator.
 * 
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return cur_point_;
}

/**
 * Iterator inequality operator.
 * 
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  //check the pointer is empty: both case is traversal over
  if(traversal_==NULL && other.traversal_==NULL) return false;
  if(traversal_==NULL || other.traversal_==NULL) return true;  
  //now, on null pointer
  //check empty first
  if(traversal_->empty()&&other.traversal_->empty()) return false;
  if(traversal_->empty()||other.traversal_->empty()) return true; 

  //both case is traversal not over yet
  if(cur_point_ ==other.cur_point_) return true;
  
  return false;
}
