#include "f_math.h"
#include "utils.h"

int FPMake(int number){
  return number << 9;
}

int FPFloor(int FPNumber){
  return FPNumber >> 9;
}

int abs(int c)
{
  return c >= 0 ? c : -c;
}

short int abs(short int c)
{
  return c >= 0 ? c : -c;
}

int sin(int FPAngle)
{
  int s = FPAngle >> 7;
  while (s < 0)
    s += 1440;

  while (s >= 1440)
    s -= 1440;

  return sinTable[s] - (1 << 9);
}

int cos(int FPAngle)
{
  return sin(FPAngle + (90 << 9));
}