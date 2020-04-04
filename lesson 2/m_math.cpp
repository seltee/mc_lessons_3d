#include "m_math.h"
#include "f_math.h"
#include "../tools/core.h"

void MIdentity(int matrix[16])
{
  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = ONE;
  matrix[5] = ONE;
  matrix[10] = ONE;
  matrix[15] = ONE;
}

void MMultiply(int matrix[16], int mul[16], int result[16])
{
  result[0] = FPMutliply(matrix[0], mul[0]) + FPMutliply(matrix[1], mul[4]) + FPMutliply(matrix[2], mul[8]) + FPMutliply(matrix[3], mul[12]);
  result[1] = FPMutliply(matrix[0], mul[1]) + FPMutliply(matrix[1], mul[5]) + FPMutliply(matrix[2], mul[9]) + FPMutliply(matrix[3], mul[13]);
  result[2] = FPMutliply(matrix[0], mul[2]) + FPMutliply(matrix[1], mul[6]) + FPMutliply(matrix[2], mul[10]) + FPMutliply(matrix[3], mul[14]);
  result[3] = FPMutliply(matrix[0], mul[3]) + FPMutliply(matrix[1], mul[7]) + FPMutliply(matrix[2], mul[11]) + FPMutliply(matrix[3], mul[15]);
  result[4] = FPMutliply(matrix[4], mul[0]) + FPMutliply(matrix[5], mul[4]) + FPMutliply(matrix[6], mul[8]) + FPMutliply(matrix[7], mul[12]);
  result[5] = FPMutliply(matrix[4], mul[1]) + FPMutliply(matrix[5], mul[5]) + FPMutliply(matrix[6], mul[9]) + FPMutliply(matrix[7], mul[13]);
  result[6] = FPMutliply(matrix[4], mul[2]) + FPMutliply(matrix[5], mul[6]) + FPMutliply(matrix[6], mul[10]) + FPMutliply(matrix[7], mul[14]);
  result[7] = FPMutliply(matrix[4], mul[3]) + FPMutliply(matrix[5], mul[7]) + FPMutliply(matrix[6], mul[11]) + FPMutliply(matrix[7], mul[15]);
  result[8] = FPMutliply(matrix[8], mul[0]) + FPMutliply(matrix[9], mul[4]) + FPMutliply(matrix[10], mul[8]) + FPMutliply(matrix[11], mul[12]);
  result[9] = FPMutliply(matrix[8], mul[1]) + FPMutliply(matrix[9], mul[5]) + FPMutliply(matrix[10], mul[9]) + FPMutliply(matrix[11], mul[13]);
  result[10] = FPMutliply(matrix[8], mul[2]) + FPMutliply(matrix[9], mul[6]) + FPMutliply(matrix[10], mul[10]) + FPMutliply(matrix[11], mul[14]);
  result[11] = FPMutliply(matrix[8], mul[3]) + FPMutliply(matrix[9], mul[7]) + FPMutliply(matrix[10], mul[11]) + FPMutliply(matrix[11], mul[15]);
  result[12] = FPMutliply(matrix[12], mul[0]) + FPMutliply(matrix[13], mul[4]) + FPMutliply(matrix[14], mul[8]) + FPMutliply(matrix[15], mul[12]);
  result[13] = FPMutliply(matrix[12], mul[1]) + FPMutliply(matrix[13], mul[5]) + FPMutliply(matrix[14], mul[9]) + FPMutliply(matrix[15], mul[13]);
  result[14] = FPMutliply(matrix[12], mul[2]) + FPMutliply(matrix[13], mul[6]) + FPMutliply(matrix[14], mul[10]) + FPMutliply(matrix[15], mul[14]);
  result[15] = FPMutliply(matrix[12], mul[3]) + FPMutliply(matrix[13], mul[7]) + FPMutliply(matrix[14], mul[11]) + FPMutliply(matrix[15], mul[15]);
}

void MMatrixMultipyVector(const int matrix[16], const int mul[4], int result[4])
{
  result[0] = FPMutliply(matrix[0], mul[0]) + FPMutliply(matrix[1], mul[1]) + FPMutliply(matrix[2], mul[2]) + FPMutliply(matrix[3], mul[3]);
  result[1] = FPMutliply(matrix[4], mul[0]) + FPMutliply(matrix[5], mul[1]) + FPMutliply(matrix[6], mul[2]) + FPMutliply(matrix[7], mul[3]);
  result[2] = FPMutliply(matrix[8], mul[0]) + FPMutliply(matrix[9], mul[1]) + FPMutliply(matrix[10], mul[2]) + FPMutliply(matrix[11], mul[3]);
  result[3] = FPMutliply(matrix[12], mul[0]) + FPMutliply(matrix[13], mul[1]) + FPMutliply(matrix[14], mul[2]) + FPMutliply(matrix[15], mul[3]);
}

void MVectorMultipyMatrix(const int mul[4], const int matrix[16], int result[4])
{
  result[0] = FPMutliply(matrix[0], mul[0]) + FPMutliply(matrix[4], mul[1]) + FPMutliply(matrix[8], mul[2]) + FPMutliply(matrix[12], mul[3]);
  result[1] = FPMutliply(matrix[1], mul[0]) + FPMutliply(matrix[5], mul[1]) + FPMutliply(matrix[9], mul[2]) + FPMutliply(matrix[13], mul[3]);
  result[2] = FPMutliply(matrix[2], mul[0]) + FPMutliply(matrix[6], mul[1]) + FPMutliply(matrix[10], mul[2]) + FPMutliply(matrix[14], mul[3]);
  result[3] = FPMutliply(matrix[3], mul[0]) + FPMutliply(matrix[7], mul[1]) + FPMutliply(matrix[11], mul[2]) + FPMutliply(matrix[15], mul[3]);
}

void MTransition(int matrix[16], int FPX, int FPY, int FPZ)
{
  MIdentity(matrix);
  matrix[3] = FPX;
  matrix[7] = FPY;
  matrix[11] = FPZ;
}

void MScale(int matrix[16], int FPX, int FPY, int FPZ)
{
  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = FPX;
  matrix[5] = FPY;
  matrix[10] = FPZ;
  matrix[15] = ONE;
}

void MRotationX(int matrix[16], int FPAngle)
{
  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = ONE;
  matrix[5] = cos(FPAngle);
  matrix[6] = -sin(FPAngle);
  matrix[9] = sin(FPAngle);
  matrix[10] = cos(FPAngle);
  matrix[15] = ONE;
}

void MRotationY(int matrix[16], int FPAngle)
{
  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = cos(FPAngle);
  matrix[2] = sin(FPAngle);
  matrix[5] = ONE;
  matrix[8] = -sin(FPAngle);
  matrix[10] = cos(FPAngle);
  matrix[15] = ONE;
}

void MRotationZ(int matrix[16], int FPAngle)
{
  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = cos(FPAngle);
  matrix[1] = -sin(FPAngle);
  matrix[4] = sin(FPAngle);
  matrix[5] = cos(FPAngle);
  matrix[10] = ONE;
  matrix[15] = ONE;
}

void MCopy(int source[16], int dest[16])
{
  memcpy(dest, source, 16 * sizeof(int));
}

void MPerspective(int matrix[16])
{
  int aspect = FPMake(1);
  int fovy = FPMake(100);
  int near = FPMake(1);
  int far = FPMake(80);
  int divfov = FPDivide(fovy, FPMake(2));
  int ctgCalc = ctg(divfov);
  int Q = FPDivide(far, far - near);

  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = ctgCalc;
  matrix[5] = ctgCalc;
  matrix[10] = Q;
  matrix[11] = ONE;
  matrix[14] = -FPMutliply(Q, near);
}

void MOrtogonal(int matrix[16])
{
  int left = -FPMake(1);
  int right = FPMake(1);
  int top = -FPMake(1);
  int bottom = FPMake(1);
  int near = FPDivide(FPMake(1), FPMake(4));
  int far = FPMake(100);

  memset(matrix, 0, sizeof(int) * 16);
  matrix[0] = FPDivide(FPMake(2), (right - left));
  matrix[3] = -FPDivide((right + left), (right - left));
  matrix[5] = FPDivide(FPMake(2), (top - bottom));
  matrix[7] = -FPDivide((top + bottom), (top - bottom));
  matrix[10] = -FPDivide(FPMake(2), (far - near));
  matrix[11] = -FPDivide((far + near), (far - near));
  matrix[15] = ONE;
}