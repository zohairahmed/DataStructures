#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;


  MyColorPicker::MyColorPicker(HSLAPixel color): col_(color){

  }
/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  if (x % 5 == 0 && y % 5 == 0){
    changeColH();
  }
  else if (x % 5 == 0){
    changeColS();
  }
  else if (y % 5 == 0){
    changeColL();
  }
  /* @todo [Part 3] */
  return col_;
}

void MyColorPicker::changeColH(){
  col_.h += 10;
  if (col_.h > 360)
    col_.h -= 360;
}
void MyColorPicker::changeColL(){
  if (col_.l > .9){
    double delt = 1 - col_.l;
    col_.l = 1;
    col_.l -= delt;
  }
  else {
    col_.l += 1;
  }

}
void MyColorPicker::changeColS(){
  if (col_.s > .9){
    double delt = 1 - col_.s;
    col_.s = 1;
    col_.s -= delt;
  }
  else {
    col_.s += 1;
  }
}
