#include "StickerSheet.h"
#include "cs225/PNG.h"
#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
#include <math.h>

using namespace std;    //test

namespace cs225
{
    StickerSheet::StickerSheet()
    {
        //return_image = nullptr;
       
        this->arr_pointer = new Image*[5];
        this->arr_x = new unsigned int[5];
        this->arr_y = new unsigned int[5]; 
        //this->arr_pointer[0] = &picture;
        cur_counter=0;
        //create the base picture pointer
        base_pointer = new Image();
        this->arr_couter = 5;

        //initialization 3.7
        for(unsigned x=0;x<arr_couter;x++)
        {
            arr_pointer[x]=nullptr;
        }
    }
    //helper function
        //copy a new array and a counter
    void StickerSheet::copy(const StickerSheet &other)
    {
        this->arr_pointer = new Image*[other.arr_couter];
        this->arr_couter = other.arr_couter;
        this->base_pointer = new Image;
        *base_pointer = *other.base_pointer;
        this->flag = other.flag;
        this->arr_x = new unsigned int[arr_couter];
        this->arr_y = new unsigned int[arr_couter];        
        cur_counter = other.cur_counter;
        //copy pointer of each image and x,y coor of each image
            //cout<<"cur_counter "<<cur_counter<<"arr_counter "<< arr_couter<<endl;

        //initialization 3.7
        for(unsigned x=0;x<arr_couter;x++)
        {
            arr_pointer[x]=nullptr;
        }

        for(unsigned int x=0;x<=cur_counter;x++)
        {
            this->arr_pointer[x] = other.arr_pointer[x];
            this->arr_x [x] = other.arr_x[x];
            this->arr_y[x] = other.arr_y[x];
        }
    }
        //in pair with copy 
    void StickerSheet::destruct()
    {
        delete [] arr_pointer;
        delete [] arr_x;
        delete [] arr_y;
        delete base_pointer;
        // delete base_pointer;
        base_pointer = nullptr;
        arr_couter = 0;
        cur_counter = 0;
        arr_pointer = nullptr;

        //if(return_image !=nullptr){delete return_image;}
    }

    //custom constructor 
    StickerSheet::StickerSheet(const Image &picture, unsigned max)
    {
        //return_image = nullptr;
        flag=0;//indicate do not equal 
        this->arr_pointer = new Image*[max];
        this->arr_x = new unsigned int[max];
        this->arr_y = new unsigned int[max]; 
        //this->arr_pointer[0] = &picture;
        cur_counter=0;
        //create the base picture pointer
        base_pointer = new Image(picture);
        this->arr_couter = max;

        //initialization 3.7
        for(unsigned x=0;x<arr_couter;x++)
        {
            arr_pointer[x]=nullptr;
        }
    }
    //destructor
    StickerSheet::~StickerSheet()
    {
        // delete base_pointer;
        // base_pointer = nullptr;
        destruct();
    }
    // c.c.
    StickerSheet::StickerSheet(const StickerSheet & other)
    {
        copy(other);
    }

    //a.o
    const StickerSheet& StickerSheet::operator= (const StickerSheet &other)
    {
        delete [] arr_pointer;
        delete [] arr_x;
        delete [] arr_y;
        //3.6
        delete base_pointer;
        copy(other);
        return *this;
    }
    //
    void StickerSheet::changeMaxStickers(unsigned max)
    {
        //return if no need to change
        if(max==this->arr_couter) return;
        
        //create a new array pointers
        Image **temporary_pointer = new Image*[max];
        unsigned int *temporary_x = new unsigned int[max];
        unsigned int *temporary_y = new unsigned int[max];

        // if longer
        if(max>=this->arr_couter)
        {
        for(unsigned int x=0;x<arr_couter;x++)
        {
            temporary_pointer[x] = this->arr_pointer[x];
            temporary_x[x] = this->arr_x[x];
            temporary_y[x] = this->arr_y[x];
        }
        delete [] arr_pointer;
        delete [] arr_x;
        delete [] arr_y;
        arr_pointer = temporary_pointer;
        arr_x = temporary_x;
        arr_y = temporary_y;
        arr_couter = max;
        }
        //shorter in this case
        else  
        {
            arr_couter=max;
        for(unsigned int x=0;x<arr_couter;x++)
        {
            temporary_pointer[x] = this->arr_pointer[x];
            temporary_x[x] = this->arr_x[x];
            temporary_y[x] = this->arr_y[x];
        }
        delete [] arr_pointer;
        delete [] arr_x;
        delete [] arr_y;
        arr_pointer = temporary_pointer;
        arr_x = temporary_x;
        arr_y = temporary_y;
        arr_couter = max;
        //test
        cur_counter = max;
        cout<<cur_counter<< " "<< arr_couter<<endl;
        }
    }
    int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y)
    {
        //3.7 new 
        for(unsigned int add_counter=0;add_counter<=cur_counter;add_counter++)
        {
            if(nullptr==arr_pointer[add_counter]) 
            {
                arr_pointer[add_counter] = &sticker;
                arr_x[add_counter] = x;
                arr_y[add_counter] = y;
                if(add_counter==cur_counter) cur_counter++;
                return add_counter;
            }

        }
        return -1;
        /* version before 3.7
        //if(flag==1 ||cur_counter==arr_couter )
        if(cur_counter>=arr_couter)
        {   
            return 0;
        }
            arr_pointer[cur_counter] = &sticker;


            arr_x[cur_counter] = x;

            arr_y[cur_counter] = y;
            cur_counter++;
            //if(cur_counter<arr_couter-1) cur_counter++;
            //if(cur_counter==arr_couter-1) flag = 1;
            //cur_counter++;
        return 1;
        */
    }
    bool StickerSheet::translate (unsigned index, unsigned x, unsigned y)
    {
        //if valid
        //cout<<cur_counter<<endl;
        //if(    (index<cur_counter|| (index==cur_counter && flag==1) ) && arr_pointer[index]!=nullptr)
        if(index<cur_counter )
        {
            arr_x[index] = x;
            arr_y[index] = y;
            return true;
        }   
        return false;
    }
    void StickerSheet::removeSticker (unsigned index)
    {
        //if(    (index<cur_counter|| (index==cur_counter && flag==1) ) && arr_pointer[index]!=nullptr)
        if(index<cur_counter && arr_pointer[index]!=nullptr)
        {
            arr_pointer[index] = nullptr;
            arr_x[index] = -1;
            arr_y[index] = -1;
        }
    }
    Image* StickerSheet::getSticker (unsigned index) const
    {
        if(index<cur_counter && arr_pointer[index]!=nullptr)
        //if(    (index<cur_counter|| (index==cur_counter && flag==1) ) && arr_pointer[index]!=nullptr)
        {
            //cout<<"arr_pointer[1]"<< arr_pointer[1]<<endl;
            return arr_pointer[index];
        }   
        return NULL;
    }
    Image StickerSheet::render() const
    {
        //find the size of the picture first
        unsigned int image_width = base_pointer->width();
        unsigned int image_height = base_pointer->height();
        unsigned int compare_variable = 0;
            //  cout<<"cur_counter"<< cur_counter<<endl;
            //  cout<<"arr_counter"<< arr_couter<<endl;
            //  cout<<"arr_counter"<< arr_pointer[1]<<" "<<arr_pointer[2]<<" "<<arr_x[1]<<endl;
        
        //unsigned int another_cur_counter ;
        //if(flag==1) {another_cur_counter = cur_counter;}
        //else{another_cur_counter=cur_counter-1;}
        for(unsigned int i=0;i<cur_counter;i++)
        {
            //continue if invalid
            if(arr_pointer[i]==nullptr){continue;}
            //find largest width and height
            compare_variable = arr_pointer[i]->width() + arr_x[i];
            if(compare_variable>=image_width)
            {
                image_width=compare_variable;
            }
            compare_variable = arr_pointer[i]->height() + arr_y[i];
            if(compare_variable>=image_height)
            {
                image_height=compare_variable;
            }
        }
    
      // cout<<"0"<<endl;
        Image return_image = Image();
        return_image.resize(image_width,image_height);
        //draw all the picture

        unsigned int cur_width = base_pointer->width();
        unsigned int cur_height= base_pointer->height();

        //draw base picture
        for(unsigned int x=0;x < cur_width; x++)
        {
            for(unsigned int y=0; y < cur_height; y++)
            {
                HSLAPixel* cur_pixel = base_pointer->getPixel(x,y);
                if(cur_pixel->a==0){continue;}
                else
                {
                    *(return_image.getPixel(x,y)) = *cur_pixel;
                }
            }
        }
          // cout<<"0"<<endl;
        //draw every pixel in each picture
        for(unsigned int i=0;i<cur_counter;i++)
        {
            //if invalie, continue
            if(arr_pointer[i]==nullptr){continue;}

            cur_width = arr_pointer[i]->width();
            cur_height = arr_pointer[i]->height();

            for(unsigned int x=0;x < cur_width; x++)
            {
                for(unsigned int y=0; y < cur_height; y++)
                {
                    HSLAPixel* cur_pixel = arr_pointer[i]->getPixel(x,y);
                    if(cur_pixel->a==0){continue;}
                    else
                    {
                        *(return_image.getPixel(x+arr_x[i],y+arr_y[i])) = *cur_pixel;
                    }
                }
            }
        }

        return return_image;
    }
}