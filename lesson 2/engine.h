#include "f_math.h"

class Engine
{
public:
  // Creates sprite, where pixels will be drawn and sprite that will draw on screen with standart function
  bool openWindow(short int startX, short int startY, short int sizeW, short int sizeH, bool useUpScale);

  // Draw sprite, that represents the window
  void drawWindow();

  // Clear owr look sprite
  void clear();

  // Draw single pixel with check where to draw
  void drawPixel(int px, int py, unsigned char color);

  // Draw line on our screen sprite
  void drawLine(int startX, int startY, int endX, int endY, unsigned char color);

private:
  short int startX, startY, sizeW, sizeH, screenFullSize;
  bool useUpScale;
  unsigned char *data;
};
