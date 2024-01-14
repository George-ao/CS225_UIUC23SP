#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 */

//get inspiration from those given colorpicker
//In MycolorPiker, I have three private variables whcih 

MyColorPicker::MyColorPicker(double hue,double multiple,double saturation,double luminance)
  : hue(hue), multiple(multiple),saturation(saturation),luminance(luminance) 
  { 

  }

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  HSLAPixel pixel(hue, saturation,luminance);
  hue = hue*multiple;
  while (hue>=360)
  {
    hue = hue - 360;
  }
  return pixel;
}
