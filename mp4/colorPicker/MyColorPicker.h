#ifndef MyColorPicker_H
#define MyColorPicker_H

#include "ColorPicker.h"
#include "../cs225/HSLAPixel.h"
#include "../Point.h"

using namespace cs225;

class MyColorPicker : public ColorPicker {
public:
  MyColorPicker(double hue,double multiple,double saturation,double luminance);
  HSLAPixel getColor(unsigned x, unsigned y);

private:
  double hue;
  double multiple;
  double saturation;
  double luminance;

};

#endif
