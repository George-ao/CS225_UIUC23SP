#ifndef  HSLAPIXEL_H
#define  HSLAPIXEL_H


namespace cs225{
class HSLAPixel
{
    public:
        double h;   //Hue value for the new pixel, in degrees [0, 360]
        double s;   //Saturation value for the new pixel, [0, 1]
        double l;   //Luminance value for the new pixel, [0, 1]
        double a;   //Alpha value for the new pixel, [0, 1]

        //default constructor
        HSLAPixel();
        //three inputs constructor
        HSLAPixel(double hue, double saturation,double luminance);  
        //four inputs constructor
        HSLAPixel(double hue, double saturation,double luminance, double alpha);  
};
}
#endif 


