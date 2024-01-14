#include <cstdlib>
#include <cmath>
#include <iostream> 
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;
// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
    HSLAPixel* pixel = new HSLAPixel(201, saturation, 0.5);         //create pixel in heap
    return pixel;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    original->readFromFile(inputFile);     //use new to create object in heap
    unsigned width = original->width();
    unsigned height = original->height();
    // Create out.png
    PNG* output;
    output= setupOutput(width, height);     //let the output be the pointer of the output image

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; 0<y && y< height; y++) {
        for (unsigned x = 1; 0<x && x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel* prev = original->getPixel(x - 1, y - 1);
            HSLAPixel* curr = original->getPixel(x, y);
            double diff = std::fabs(curr->h - prev->h);

            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            //HSLAPixel* currOutPixel = (*output).getPixel(x, y);
            if (diff > 20) {
                HSLAPixel* currOutPixel = (*output).getPixel(x, y);
                *currOutPixel = *myPixel;                               //change the value of the pixel class of the current pixel
            }
        }
    }

    // Save the output file
    output->writeToFile(outputFile);

    //  Clean up memory
    delete myPixel; myPixel=nullptr;
    delete output;  output=nullptr;
    delete original; original=nullptr;
}