// Table of precalculated sin functions. Precision is 4, so, it's 360 * 4 values
extern const short int sinTable[1440];

// Draws fixed point number on screen
void drawFPNumber(int x, int y, int number);

int orient2d(const int a[2], const int b[2], const int c[2]);

int min3(int p1, int p2, int p3);
int max3(int p1, int p2, int p3);
int min2(int p1, int p2);
int max2(int p1, int p2);

int FPDotProduct(const int vecA[3], const int vecB[3]);
void FPCrossProduct(const int vecA[3], const int vecB[3], int vecCross[3]);
void FPGetNormal(const int FP1[3], const int FP2[3], const int FP3[3], int FPResult[3]);

int FPSquareRoot(const int FPvalue);
int FPGetVectorLength(const int vec[3]);
void FPGetUnitVector(const int vec[3], int FPResult[3]);