#ifndef IMAGE_H
#define IMAGE_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

using namespace std;
namespace cs225
{
    class Image : public PNG            //inheritance from PNG class 
    {
        public:
            //Image();
            //Image(unsigned int width,unsigned int height);
            //Image const & operator= (Image const & other);
            void lighten();
            void lighten(double amount);
            void darken();
            void darken(double amount);
            void saturate();
            void saturate(double amount);
            void desaturate(); 
            void desaturate(double amount);
            void greyscale();
            void rotateColor(double degrees);
            void illify();
            void scale(double factor);
            void scale(unsigned w, unsigned h);
            //~Image();
        private:

    };
}
#endif