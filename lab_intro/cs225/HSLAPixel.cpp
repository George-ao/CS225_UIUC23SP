#include "HSLAPixel.h"

namespace cs225{
//default constructor
HSLAPixel::HSLAPixel()
{
    l=1.0;
    a=1.0;
}
//three inputs constructor
HSLAPixel::HSLAPixel(double hue, double saturation,double luminance) 
{
    h=hue;
    s=saturation;  
    l=luminance;  
    a=1.0;
}  

//four inputs constructor
HSLAPixel::HSLAPixel(double hue, double saturation,double luminance, double alpha) 
{
    h=hue;
    s=saturation;  
    l=luminance;  
    a=alpha;
}     
}