#include "engine.h"
#include "utils.h"
#include "../tools/core.h"

bool Engine::openWindow(short int startX, short int startY, short int sizeW, short int sizeH, bool useUpScale)
{
  this->startX = startX;
  this->startY = startY;
  this->sizeW = sizeW;
  this->sizeH = sizeH;
  this->useUpScale = useUpScale;

  screenFullSize = sizeW * sizeH;
  this->data = (unsigned char *)malloc(screenFullSize);
  if (this->data)
  {
    clear();
    return true;
  }
  return false;
}

void Engine::drawWindow()
{
  if (data)
  {
    displaySprite(data, startX, startY, sizeW, sizeH, SPRITE_FLAG_NO, useUpScale);
  }
}

void Engine::clear()
{
  memset(data, 0, screenFullSize);
}

void Engine::drawPixel(int px, int py, unsigned char color)
{
  if (px >= 0 && py >= 0 && px < sizeW && py < sizeH)
  {
    data[px + py * sizeW] = color;
  }
}

void Engine::drawLine(int startX, int startY, int endX, int endY, unsigned char color)
{
  int dx = abs(endX - startX);
  int sx = startX < endX ? 1 : -1;
  int dy = -abs(endY - startY);
  int sy = startY < endY ? 1 : -1;
  int err = dx + dy;

  while (true)
  {
    drawPixel(startX, startY, color);
    if (startX == endX && startY == endY)
    {
      break;
    }
    int e2 = 2 * err;
    if (e2 >= dy)
    {
      err += dy;
      startX += sx;
    }
    if (e2 <= dx)
    {
      err += dx;
      startY += sy;
    }
  }
}
