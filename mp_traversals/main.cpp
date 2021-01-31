
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"
#include <iostream>

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
  PNG png;
  png.readFromFile("tests/pacman.png");
  FloodFilledImage image(png);

  DFS dfs(png, Point(100, 50), .2);
  HSLAPixel some(231, 1, .5);
  HSLAPixel end(45, 1, .5);
  MyColorPicker mine(some);

  image.addFloodFill(dfs, mine);

  GradientColorPicker grad(some, end, Point(100, 50), 100);
  BFS bfs(png, Point(100, 50), .2);
  image.addFloodFill(bfs, grad);

  GradientColorPicker grad2(some, end, Point(100, 150), 100);
  BFS bfs2(png, Point(100, 50), .4);
  image.addFloodFill(bfs2, grad2);

  Animation animation;
  animation = image.animate(500);

  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  std::cout << "Done animating.\n";
  lastFrame.writeToFile("myFloodFill.png");
  std::cout << "Creating gif\n";
  animation.write("myFloodFill.gif");


  return 0;
}
