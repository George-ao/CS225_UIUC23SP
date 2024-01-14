#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"

using namespace std;
namespace cs225
{
    class StickerSheet
    {
        public:
            StickerSheet(); //d.c.
            StickerSheet(const Image &picture, unsigned max);       //c.
            ~StickerSheet();                                        //d.
            StickerSheet(const StickerSheet &other);                //c.c
            const StickerSheet & operator= (const StickerSheet &other);         //a.o
            void changeMaxStickers (unsigned max)  ;                //
            int addSticker (Image &sticker, unsigned x, unsigned y);
            bool translate (unsigned index, unsigned x, unsigned y);
            void removeSticker (unsigned index);
            Image *getSticker (unsigned index) const;
            Image render () const;
            int flag;
        private:
            Image **arr_pointer;
            Image* base_pointer;
            
            unsigned int cur_counter;
            unsigned int *arr_x;
            unsigned int *arr_y;
            //count the array length of pointer
            unsigned int arr_couter;  //start from 0

            //helper func
            void copy(const StickerSheet &other);
            void destruct();

            //Image* return_image;
    };
}
#endif