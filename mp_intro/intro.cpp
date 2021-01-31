#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <math.h>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG inFile;
  inFile.readFromFile(inputFile);
  cs225::PNG outFile(inFile);

  for (unsigned x = 0; x < inFile.width(); x++){
    for (unsigned y = 0; y < inFile.height(); y++){
      outFile.getPixel(x,y) = inFile.getPixel(inFile.width() - x - 1, inFile.height() - y - 1);
    }
  }
  outFile.writeToFile(outputFile);
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < width; x++){
    for (unsigned y = 0; y < height; y++){
      png.getPixel(x, y).s = fmod((log(x*x)/log(x*y)), 1.0);
      png.getPixel(x, y).h = 359*cos(x+y)*cos(x-y);
      png.getPixel(x, y).l = .5*sin((x-y)*png.getPixel(x, y).h) + .25;
      png.getPixel(x, y).a = 1;
    }
  }


  return png;
}
