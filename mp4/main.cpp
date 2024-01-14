
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  // PNG png;      png.readFromFile("test/i.png");
  PNG png;      png.readFromFile("111.png");//("tests/i.png");
    // png.resize(500,500);
  FloodFilledImage image(png);
  BFS bfs(png, Point(200, 200), 0.05);
  DFS dfs_1(png, Point(500, 700), 0.05);  //red
  DFS dfs_2(png, Point(400, 500), 0.05);  //bluwe
  // BFS bfs_2(png, Point(400, 600), 0.05);  //another blue
  MyColorPicker my_red(0.5,1,1,0.6);
  MyColorPicker my_2(0.5,1.1,1,0.6);
  MyColorPicker my_blue(202,1,1,0.75);
  // MyColorPicker my_blue_2(202,1,0.5,0.70);
  image.addFloodFill( dfs_1, my_red);
  image.addFloodFill( bfs, my_2);
  image.addFloodFill( dfs_2, my_blue);
  // image.addFloodFill( bfs_2, my_blue_2);
  // image.addFloodFill( bfs_2, my_blue_2);
  Animation animation = image.animate(15000);
  
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  

  return 0;
}
