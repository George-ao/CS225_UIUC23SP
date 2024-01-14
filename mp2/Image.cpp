#include "cs225/PNG.h"
#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"

#include <math.h>
namespace cs225
{
    //Image::Image():PNG(){}
    //Image::Image(unsigned int width,unsigned int height):PNG(width,height){}
    //Image::~Image(){delete[] imageData_;}
    //Image::Image const & operator= (Image const & other):PNG const & operator= (other){}
    void Image::lighten()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = getPixel(x, y);
                //add 0.1 if it does not exceed 1.0    
                if(pixel_1->l+0.1<=1){pixel_1->l +=0.1;}
                else{pixel_1->l=1.0;}
            }
        }
    }

    void Image::lighten(double amount)
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->l+amount<=1){pixel_1->l +=amount;}
                else{pixel_1->l=1.0;}
            }
        }
    }
    void Image::darken()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->l-0.1>=0.0){pixel_1->l -=0.1;}
                else{pixel_1->l=0.0;}
            }
        }
    }
    void Image::darken(double amount)
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->l-amount>=0.0){pixel_1->l -=amount;}
                else{pixel_1->l=0.0;}
            }
        }
    }
    void Image::saturate()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->s+0.1<=1.0){pixel_1->s +=0.1;}
                else{pixel_1->s=1.0;}
            }
        }
    }
    void Image::saturate(double amount)
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->s+amount<=1.0){pixel_1->s +=amount;}
                else{pixel_1->s=1.0;}
            }
        }
    }
    void Image::desaturate()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->s-0.1>=0){pixel_1->s -=0.1;}
                else{pixel_1->s=0.0;}
            }
        }
    }
    void Image::desaturate(double amount )
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                if(pixel_1->s-amount>=0){pixel_1->s -=amount;}
                else{pixel_1->s=0.0;}
            }
        }
    }
    void Image::greyscale()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                //add if it does not exceed 1.0    
                pixel_1->s=0;
            }
        }
    }
    void Image::rotateColor(double degrees)
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
                pixel_1->h = fmod(degrees+pixel_1->h,360.0);
                if(pixel_1->h<0){pixel_1->h+=360;}
            }
        }
    }
    void Image::illify()
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        //loop through all the pixel_1 and increase i by 0.1 respectively
        for (unsigned x = 0; x < width; x++)
        {
            for (unsigned y = 0; y < height; y++) 
            {
                HSLAPixel *pixel_1 = this->getPixel(x, y);                  
            //if in the range of [0,216]
            if (0 <= pixel_1->h && pixel_1->h <= 216)
            {
            //if the pixel_1's hue value is closer to orange than blue then orange
            if( abs(pixel_1->h-11) < abs(pixel_1->h-216))
            {
                pixel_1->h=11;
            }
            else{pixel_1->h=216;}
            }
            //if not 
            else
            {
                if(pixel_1->h>=294){pixel_1->h=11;}
                else{pixel_1->h=216;}
            }
            }
        }
    }
    void Image::scale(double factor)
    {
        //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();
        //make a new picture with scaled size
        unsigned int new_width=floor(factor*width);
        unsigned int new_height=floor(factor*height);
        Image* new_image= new Image();
        new_image->resize(new_width,new_height);
        for(unsigned x = 0; x < new_width; x++)
        {
            for(unsigned y = 0; y < new_height; y++)
            {        
                unsigned x_coor = x/factor;
                unsigned y_coor = y/factor;
                HSLAPixel *pixel_1 = this->getPixel(x_coor,y_coor);          //original
                HSLAPixel *pixel_2 = new_image->getPixel(x,y);          //new  
                *pixel_2=*pixel_1;
            }
        }
        *this=*new_image;
        //test
        delete new_image;
    }
    void Image::scale(unsigned w, unsigned h)
    {
       //get info about image first
        unsigned width = this->width();
        unsigned height = this->height();

        double factor1 = double(w)/width;
        double factor2 = double(h)/height;
        double factor;
        if(factor1>factor2) factor = factor2;
        else factor = factor1;
 
        //make a new picture with scaled size
        unsigned int new_width=ceil(factor*width);
        unsigned int new_height=ceil(factor*height);
        Image* new_image= new Image();
        new_image->resize(new_width,new_height);
        for(unsigned x = 0; x < new_width; x++)
        {
            for(unsigned y = 0; y < new_height; y++)
            {        
                unsigned x_coor = x/factor;
                unsigned y_coor = y/factor;
                HSLAPixel *pixel_1 = this->getPixel(x_coor,y_coor);          //original
                HSLAPixel *pixel_2 = new_image->getPixel(x,y);          //new  
                *pixel_2=*pixel_1;
            }
        }
        *this=*new_image;
        //test
        delete new_image;
    } 

}