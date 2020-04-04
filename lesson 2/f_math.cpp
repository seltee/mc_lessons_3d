#include "f_math.h"

int FPMake(int number)
{
  return number >= 0 ? number << FSHIFT : (number << FSHIFT) + MAX_FRACTION;
}

int FPFloor(int FPNumber)
{
  return FPNumber >> FSHIFT;
}

int FPFraction(int FPNumber)
{
  return FPNumber & MAX_FRACTION;
}

int FPMutliply(int FPNumber1, int FPNumber2)
{
  int fPart = FPNumber1 * (FPNumber2 >> FSHIFT);
  int sPart = FPNumber1 * (FPNumber2 & MAX_FRACTION) / MAX_FRACTION;
  return fPart + sPart;
}

int FPDivide(int FPNumber1, int FPNumber2)
{
  return FPMutliply(FPNumber1, (ONE * ONE) / FPNumber2);
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
  int s = FPAngle >> FSHIFT << 2;
  while (s < 0)
    s += 1440;

  while (s >= 1440)
    s -= 1440;

  return sinTable[s] - ONE;
}

int cos(int FPAngle)
{
  return sin(FPAngle + (90 << FSHIFT));
}

int ctg(int FPAngle)
{
  int sn = sin(FPAngle);
  if (sn != 0){
    return FPDivide(cos(FPAngle), sn);
  } else {
    return 0;
  }
}
