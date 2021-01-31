#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

FloodFilledImage::~FloodFilledImage(){
  delete initialPic;
}

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  initialPic = new PNG(png);
}

/**
 * Adds a FloodFill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  its.push_back(&traversal);
  cps.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) const {
  Animation animation;
  animation.addFrame(*initialPic);
  for (size_t i = 0; i < its.size(); i++){
    int count = 0;
    for (const Point & p : *its[i]){
      HSLAPixel & newPix = initialPic->getPixel(p.x, p.y);
      HSLAPixel col = cps[i]->getColor(p.x, p.y);

      newPix.h = col.h;
      newPix.s = col.s;
      newPix.l = col.l;
      newPix.a = col.a;
      count++;
      if (count % frameInterval < 1){
        animation.addFrame(*initialPic);
      }
    }

  }
  animation.addFrame(*initialPic);
  // start with initial image
  // loop through every imageTraversal and colorPicker and operate on the latest frame
  // update the png based on the current value of whatever imagetraversal is occurring

  /** @todo [Part 2] */
  return animation;
}
