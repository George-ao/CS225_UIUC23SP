/**
 * Copyright 2011 University of Illinois at Urbana-Champaign
 * CS 225 Lab 04 C++ Object Oriented Programming
 * Authors:
 *   Simon Krueger <skruege2@illinois.edu>
 *   Modified (FA17): Jordi Paris Ferrer <parisfe2@illinois.edu>
 */

#ifndef FLOWER_H_
#define FLOWER_H_

#include "shape.h"

#include "shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
class Flower : public Drawable
{
  private:
    Shape* stem;
    Shape* pistil; // center piece of flower
    Shape* leaf;

    void drawPetals(PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    void draw(PNG* canvas) const;
    //new destructor
    ~Flower();
    //copy constructor
   // Flower& operator=(const Flower &s);
};

#endif // FLOWER_H_
