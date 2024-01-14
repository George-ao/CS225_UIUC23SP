#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "StickerSheet.h"
#include "Image.h"
#include <iostream>
#include "cs225/HSLAPixel.h"
using namespace cs225;

using namespace std;


int main() {
  Image i;
  Image minion_1;
  Image eat;
  Image out;

  i.readFromFile("i.png");
  minion_1.readFromFile("111.png");
  eat.readFromFile("eat.png");

  StickerSheet output(minion_1,3);

  //cout<<"1"<<endl;
  output.addSticker(eat,500,500);

  //cout<<"1"<<endl;
  output.addSticker(i, 2500, 2500);

  //cout<<"1"<<endl;
  output.addSticker(i, 0, 0);

  //cout<<"1"<<endl;
  //  output.addSticker(minion_2, 500, 500); 

  out = output.render();
  //cout<<"1"<<endl;
  out.writeToFile("myImage.png");

  return 0;
}