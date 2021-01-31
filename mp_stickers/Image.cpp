#include "Image.h"
#include "cs225/PNG.h"
#include "math.h"

Image::~Image(){}

// void Image::_copy(const Image &other){
//   this->resize(other.width(), other.height());
//   for (unsigned x = 0; x < other.width(); x++){
//     for (unsigned y = 0; y < other.height(); y++){
//       cs225::HSLAPixel & temp = this->getPixel(x,y);
//       temp.h = other.getPixel(x, y).h;
//       temp.s = other.getPixel(x, y).s;
//       temp.l = other.getPixel(x, y).l;
//       temp.a = other.getPixel(x, y).a;
//     }
//   }
//   x_ = other.x_;
//   y_ = other.y_;
// }

Image::Image(){
  x_ = 0;
  y_ = 0;
}
//
Image::Image(unsigned int width, unsigned int height, unsigned int x, unsigned int y) : cs225::PNG(width, height){
  x_ = x;
  y_ = y;

}
// Image::Image(const Image &other): cs225::PNG(other.width(), other.height()){
//   // _copy(other);
// }

// const Image& Image::operator= (const Image &other){
//   if (*this != other){
//     _copy(other);
//   }
//   return *this;
// }

void Image::lighten(){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).l >= .9){
        this->getPixel(x, y).l = 1;
      }
      else {
        this->getPixel(x, y).l += .1;
      }
    }
  }
}


void Image::lighten(double amount){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).l + amount > 1){
        this->getPixel(x, y).l = 1;
      }
      else {
        this->getPixel(x, y).l += amount;
      }
    }
  }
}



void Image::darken(){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).l <= .1){
        this->getPixel(x, y).l = 0;
      }
      else {
        this->getPixel(x, y).l -= .1;
      }
    }
  }
}

void Image::darken(double amount){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).l - amount < 0){
        this->getPixel(x, y).l = 0;
      }
      else {
        this->getPixel(x, y).l -= amount;
      }
    }
  }
}

void Image::saturate(){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).s >= .9){
        this->getPixel(x, y).s = 1;
      }
      else {
        this->getPixel(x, y).s += .1;
      }
    }
  }
}

void Image::saturate(double amount){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).s + amount > 1){
        this->getPixel(x, y).s = 1;
      }
      else {
        this->getPixel(x, y).s += amount;
      }
    }
  }
}

void Image::desaturate(){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).s <= .1){
        this->getPixel(x, y).s = 0;
      }
      else {
        this->getPixel(x, y).s -= .1;
      }
    }
  }
}

void Image::desaturate(double amount){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x, y).s - amount < 0){
        this->getPixel(x, y).s = 0;
      }
      else {
        this->getPixel(x, y).s -= amount;
      }
    }
  }
}

void Image::grayscale(){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      cs225::HSLAPixel pixel = this->getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }
}

void Image::rotateColor(double degrees){
  unsigned x,y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      getPixel(x,y).h += degrees;
      getPixel(x,y).h = fmod(getPixel(x,y).h, 360);
      if (getPixel(x,y).h < 0){
        getPixel(x,y).h += 360;
      }


    }
  }
}

void Image::illinify(){
  unsigned x, y;
  for (x = 0; x < this->width(); x++){
    for (y = 0; y < this->height(); y++){
      if (this->getPixel(x,y).h > 294 || this->getPixel(x,y).h < 114){
        this->getPixel(x,y).h = 11;
      }
      else{
        this->getPixel(x,y).h = 216;
      }
    }
  }
}

void Image::scale(double factor){
  unsigned newWidth = this->width() * factor;
  unsigned newHeight = this->height() * factor;
  Image newIm(newWidth, newHeight, 0, 0);
  for (unsigned x = 0; x < newWidth; x++){
    for (unsigned y = 0; y < newHeight; y++){
      cs225::HSLAPixel & temp = newIm.getPixel(x,y);
      temp.h = this->getPixel(x/factor, y/factor).h;
      temp.s = this->getPixel(x/factor, y/factor).s;
      temp.l = this->getPixel(x/factor, y/factor).l;
      temp.a = this->getPixel(x/factor, y/factor).a;
    }
  }
  this->resize(newWidth, newHeight);
  // this->_copy(newIm);
  for (unsigned x = 0; x < this->width(); x++){
    for (unsigned y = 0; y < this->height(); y++){
      cs225::HSLAPixel & temp = this->getPixel(x,y);
      temp.h = newIm.getPixel(x, y).h;
      temp.s = newIm.getPixel(x, y).s;
      temp.l = newIm.getPixel(x, y).l;
      temp.a = this->getPixel(x, y).a;
    }
  }

}

void Image::scale(unsigned w, unsigned h){
  double nw = (double) w, nh = (double) h;
  double widthFactor = nw/this->width(), heightFactor = nh/this->height();
  if (widthFactor > heightFactor){
    scale(heightFactor);
  }
  else {
    scale(widthFactor);
  }
}

unsigned int Image::getX(){
  return x_;
}

unsigned int Image::getY(){
  return y_;
}

void Image::setX(unsigned int x){
  x_ = x;
}

void Image::setY(unsigned int y){
  y_ = y;
}
