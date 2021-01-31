/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet{
  private:
    Image * base;
    Image ** images;
    int * stickerLoc;
    unsigned max_;
    void _destroy();
    void copy (const StickerSheet &other);
    void increaseMaxStickers(unsigned max);
    void decreaseMaxStickers(unsigned max);
  public:
    StickerSheet(const Image & picture, unsigned max);
    ~StickerSheet();
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator= (const StickerSheet &other);
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image * getSticker(unsigned index);
    Image render() const;
    Image * getBase() const;
    int getMax() const;
};
