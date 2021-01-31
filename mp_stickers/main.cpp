#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image backGround;
  Image sS;
  Image ultimate;
  Image trackSuit;
  backGround.readFromFile("Background.png");
  sS.readFromFile("SS.png");
  ultimate.readFromFile("Ultimate.png");
  trackSuit.readFromFile("Lame.png");
  sS.scale(1.75);

  StickerSheet toRender(backGround, 3);
  toRender.addSticker(ultimate, 125, 450);
  toRender.addSticker(sS, 125, 0);
  toRender.addSticker(trackSuit, 0, 920);

  toRender.render().writeToFile("myImage.png");


  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
