#include <string>
#include "cs225/PNG.h" //include the class for PNG use
#include "cs225/HSLAPixel.h"
#include "mp1.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    //create a empty PNG
    PNG picture1;
    picture1.readFromFile(inputFile);

    //rotate
        //get height and width of the picture
    unsigned int width = picture1.width();
    unsigned int height = picture1.height();
        //define a pixel to store the temporary value
    HSLAPixel pixel_store;
        for (unsigned x = 0; x < width; x++) {
            for (unsigned y = 0; y < height/2; y++) {
                //rotation
            HSLAPixel *pixel_1 = picture1.getPixel(x, y);
            HSLAPixel *pixel_2 = picture1.getPixel(width-x-1, height-y-1);
            pixel_store = *pixel_1;
            *pixel_1 = *pixel_2;
            *pixel_2= pixel_store;
            }
        }
        //if the height is not multiple of two, we still have onel line to rotate
        if(height%2!=0)   
        { 
        unsigned int y_last_line=height/2;  
        for(unsigned x=0; x <= width/2-1; x++)
        {
            HSLAPixel *pixel_1 = picture1.getPixel(x, y_last_line);
            HSLAPixel *pixel_2 = picture1.getPixel(width-x-1, height-y_last_line-1);
            pixel_store = *pixel_1;
            *pixel_1 = *pixel_2;
            *pixel_2= pixel_store;
        }
        }
    //write to output PNG
    picture1.writeToFile(outputFile);
}
