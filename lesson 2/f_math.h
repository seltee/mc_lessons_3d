#include "utils.h"

// This is out fixed point contants. FSHIFT states how much bits will be after point
#define FSHIFT 9
#define ONE (1 << FSHIFT)
#define MAX_FRACTION (ONE - 1)

// Make fixed point from integer
int FPMake(int number);

// Get integer part from gixed point
int FPFloor(int FPNumber);

// Get fraction part from fixed point
int FPFraction(int FPNumber);

// Multipy
int FPMutliply(int FPNumber1, int FPNumber2);

// Divide
int FPDivide(int FPNumber1, int FPNumber2);

// Remove sign
int abs(int c);
short int abs(short int c);

int sin(int FPAngle);
int cos(int FPAngle);
int ctg(int FPAngle);
