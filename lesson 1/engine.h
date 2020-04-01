#include "f_math.h"

class Engine
{
public:
  bool openWindow(short int startX, short int startY, short int sizeW, short int sizeH, bool useUpScale);
  void drawWindow();

  void clear();
  void drawPixel(int px, int py, unsigned char color);
  void drawLine(int startX, int startY, int endX, int endY, unsigned char color);

private:
  short int startX, startY, sizeW, sizeH, screenFullSize;
  bool useUpScale;
  unsigned char *data;
};
