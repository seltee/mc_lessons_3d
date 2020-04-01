#include "../tools/core.h"
#include "engine.h"
#include "utils.h"
#include "f_math.h"

Engine engine;

void drawRect(int x, int y, int size, int angle, char color)
{
  int x0 = x + FPFloor(cos(angle) * size);
  int y0 = y + FPFloor(sin(angle) * size);
  int x1 = x + FPFloor(cos(angle + FPMake(90)) * size);
  int y1 = y + FPFloor(sin(angle + FPMake(90)) * size);
  int x2 = x + FPFloor(cos(angle + FPMake(180)) * size);
  int y2 = y + FPFloor(sin(angle + FPMake(180)) * size);
  int x3 = x + FPFloor(cos(angle + FPMake(270)) * size);
  int y3 = y + FPFloor(sin(angle + FPMake(270)) * size);

  engine.drawLine(x0, y0, x1, y1, color);
  engine.drawLine(x1, y1, x2, y2, color);
  engine.drawLine(x2, y2, x3, y3, color);
  engine.drawLine(x0, y0, x3, y3, color);
}

int main()
{
  setSpriteLimit(10);
  setFPS(30);

  engine.openWindow(40, 0, 120, 120, true);

  int d = 0;
  int p = 1;
  int angle = 0;
  int addAngle = FPMake(1);

  while (1)
  {
    engine.clear();

    angle += addAngle;

    drawRect(60, 60, 30, angle, 3);
    drawRect(60, 60, 40, -angle, 2);
    drawRect(60, 60, 50, angle*2, 4);
    drawRect(60, 60, 60, -angle*3, 5);

    engine.drawWindow();
    sync();
  }
}