#include "StickerSheet.h"
#include "cs225/PNG.h"
#include <iostream>

void StickerSheet::copy(const StickerSheet &other){
  max_ = other.getMax();
  base = new Image(*(other.getBase()));
  images = new Image*[max_];
  stickerLoc = new int[max_];
  // base->resize(other.getBase()->width(), other.getBase()->height());
  *base = *(other.getBase());
  for (unsigned x = 0; x < max_; x++){
    images[x] = NULL;
    stickerLoc[x] = 0;
    if (other.stickerLoc[x] > 0 && other.images[x] != NULL){
      images[x] = new Image(*other.images[x]);
      // images[x]->setX(other.images[x]->getX());
      // images[x]->setY(other.images[x]->getY());
      stickerLoc[x] = other.stickerLoc[x];
    }
  }
}

void StickerSheet::_destroy(){
  delete base;
  base = NULL;
  for (unsigned i = 0; i < max_; i++){
    if (stickerLoc[i] > 0 && images[i] != NULL){
      stickerLoc[i] = 0;
      delete images[i];
      images[i] = NULL;
    }
  }
  if (stickerLoc != NULL)
    delete[] stickerLoc;

  delete[] images;
  images = NULL;
}

StickerSheet::StickerSheet(const Image & picture, unsigned max){
  base = new Image(picture);
  max_ = max;
  images = new Image*[max_];
  stickerLoc = new int[max_];
  for (unsigned i = 0; i < max_; i++){
    images[i] = NULL;
    stickerLoc[i] = 0;
  }
}

StickerSheet::~StickerSheet(){
  _destroy();
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);

}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
  _destroy();
  copy(other);
  return *this;

}
void StickerSheet::changeMaxStickers(unsigned max){
  if (max == max_){
    return;
  }
  else if (max > max_){
    increaseMaxStickers(max);
  }
  else{
    decreaseMaxStickers(max);
  }
}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  sticker.setX(x);
  sticker.setY(y);

  for (unsigned i = 0; i < max_; i++){
    if (images[i] == NULL){
      images[i] = new Image(sticker);
      stickerLoc[i] = 1;
      images[i]->setX(x);
      images[i]->setY(y);
      return i;
    }
  }
  return -1;
}
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index >= max_ || images[index] == NULL || stickerLoc[index] == 0)
  return false;

  images[index]->setX(x);
  images[index]->setY(y);
  return true;
}
void StickerSheet::removeSticker(unsigned index){
  if (index >= max_ || images[index] == NULL || stickerLoc[index] == 0)
    return;

  stickerLoc[index] = 0;
  delete images[index];
  images[index] = NULL;
}
Image * StickerSheet::getSticker(unsigned index){
  return images[index];
}
Image StickerSheet::render() const{
  Image rendered(*base);
  rendered.setX(0);
  rendered.setY(0);
  unsigned maxW = rendered.width(), maxH = rendered.height();

  for (unsigned i = 0; i < max_; i++){
    if (stickerLoc[i] > 0 && images[i] != NULL){
      maxW = std::max(maxW, images[i]->width() + images[i]->getX());
      maxH = std::max(maxH, images[i]->height() + images[i]->getY());
    }
  }

  rendered.resize(maxW, maxH);
  for (unsigned i = 0; i < max_; i++){
    if (stickerLoc[i] > 0 && images[i] != NULL){
    for (unsigned x = 0; x < images[i]->width(); x++){
      for (unsigned y = 0; y < images[i]->height(); y++){
        if (images[i]->getPixel(x, y).a > 0){
          cs225::HSLAPixel & temp = rendered.getPixel(x + images[i]->getX(), y + images[i]->getY());
          cs225::HSLAPixel & currSticker = images[i]->getPixel(x, y);
          temp = currSticker;
        }
      }
    }
  }
  }

 return rendered;
}

Image* StickerSheet::getBase() const{
  return base;
}

int StickerSheet::getMax() const{
  return max_;
}

void StickerSheet::increaseMaxStickers(unsigned max){
  Image** tempIm = new Image*[max];
  int * newLoc = new int[max];
  for (unsigned x = 0; x < max; x++){
    newLoc[x] = 0;
    tempIm[x] = NULL;
    if (x < max_ && stickerLoc[x] > 0 && images[x] != NULL){
      tempIm[x] = images[x];

      stickerLoc[x] = 0;
      newLoc[x] = 1;
    }
  }
  delete[] stickerLoc;
  delete[] images;
  max_ = max;


  images = tempIm;
  stickerLoc = newLoc;
}
void StickerSheet::decreaseMaxStickers(unsigned max){
  Image** tempIm = new Image*[max];
  int* newLoc = new int[max];
  for (unsigned x = 0; x < max_; x++){
    if (x < max){
      newLoc[x] = 0;
      tempIm[x] = NULL;
      if (stickerLoc[x] > 0 && images[x] != NULL){
        tempIm[x] = images[x];
        newLoc[x]++;
        images[x] = NULL;
      }
    }
    else {
      delete images[x];
      images[x] = NULL;
    }
  }
  delete[] images;
  max_ = max;
  delete[] stickerLoc;
  stickerLoc = newLoc;
  images = tempIm;
}
