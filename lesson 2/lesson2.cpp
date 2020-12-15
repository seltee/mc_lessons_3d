#include "../tools/core.h"
#include "engine.h"
#include "utils.h"
#include "f_math.h"
#include "m_math.h"

Engine engine;
int projectionMatrix[16];

// Position ob cube points
const int cubeVertex[][3] = {
    {100, 100, 100},
    {100, 100, -100},
    {-100, 100, -100},
    {-100, 100, 100},
    {100, -100, 100},
    {100, -100, -100},
    {-100, -100, -100},
    {-100, -100, 100}};

// Connection with cube point to make triangles. 12 triangles makes 6 quads of which cube consists
const int cubeMesh[][3] = {
    {0, 1, 2},
    {0, 2, 3},
    {4, 5, 6},
    {4, 6, 7},
    {0, 1, 5},
    {0, 4, 5},
    {2, 3, 7},
    {2, 6, 7},
    {0, 4, 7},
    {0, 3, 7},
    {1, 2, 5},
    {2, 5, 6},
};

// This function turns v3 into v4 (with 1) and than multiplies matrix on it
void projectPoint(int viewModelProjectionMatrix[16], const int vertex[3], int out[4])
{
  int vertexEx[4];
  vertexEx[0] = vertex[0];
  vertexEx[1] = vertex[1];
  vertexEx[2] = vertex[2];
  vertexEx[3] = 1;

  MMatrixMultipyVector(viewModelProjectionMatrix, vertexEx, out);
}

// Draw the box
void drawBox(int x, int y, int z, int rx, int ry)
{
  int dumpMatrix[16];
  int modelMatrix[16];
  int moveMatrix[16];
  int scaleMatrix[16];
  int rotateMatrixX[16];
  int rotateMatrixY[16];

  // Setting up matricies
  MIdentity(modelMatrix);
  MTransition(moveMatrix, x, y, z);
  MRotationX(rotateMatrixX, ry);
  MRotationY(rotateMatrixY, -rx);
  MScale(scaleMatrix, FPMake(1), FPMake(1), FPMake(1));

  // Applaing tranform to model matrix. 
  // Note, that there are not viewMatrix, because it is identity matrix. It will be covered in future lessons
  // Projection matrix calculated once on the start
  MMultiply(rotateMatrixX, modelMatrix, dumpMatrix);
  MMultiply(rotateMatrixY, dumpMatrix, modelMatrix);
  MMultiply(moveMatrix, modelMatrix, dumpMatrix);
  MMultiply(scaleMatrix, dumpMatrix, modelMatrix);
  MMultiply(projectionMatrix, modelMatrix, dumpMatrix);

  MCopy(dumpMatrix, modelMatrix);

  // Drawing our 12 triangles of our box
  for (int i = 0; i < 12; i++)
  {
    int pv1 = cubeMesh[i][0];
    int pv2 = cubeMesh[i][1];
    int pv3 = cubeMesh[i][2];

    const int *p1 = cubeVertex[pv1];
    const int *p2 = cubeVertex[pv2];
    const int *p3 = cubeVertex[pv3];

    int s1[4], s2[4], s3[4];

    projectPoint(modelMatrix, p1, s1);
    projectPoint(modelMatrix, p2, s2);
    projectPoint(modelMatrix, p3, s3);

    int color = (i % 4) + 2;
    engine.drawLine(
        FPFloor(FPDivide(s1[0] * 60, s1[2])) + 60,
        FPFloor(-FPDivide(s1[1] * 60, s1[2])) + 60,
        FPFloor(FPDivide(s2[0] * 60, s2[2])) + 60,
        FPFloor(-FPDivide(s2[1] * 60, s2[2])) + 60,
        color);

    engine.drawLine(
        FPFloor(FPDivide(s2[0] * 60, s2[2])) + 60,
        FPFloor(-FPDivide(s2[1] * 60, s2[2])) + 60,
        FPFloor(FPDivide(s3[0] * 60, s3[2])) + 60,
        FPFloor(-FPDivide(s3[1] * 60, s3[2])) + 60,
        color);

    engine.drawLine(
        FPFloor(FPDivide(s3[0] * 60, s3[2])) + 60,
        FPFloor(-FPDivide(s3[1] * 60, s3[2])) + 60,
        FPFloor(FPDivide(s1[0] * 60, s1[2])) + 60,
        FPFloor(-FPDivide(s1[1] * 60, s1[2])) + 60,
        color);
  }
}

int main()
{
  setSpriteLimit(60);
  setFPS(30);

  engine.openWindow(40, 0, 120, 120, true);

  MPerspective(projectionMatrix);

  int rotX = 0, rotY = 0;
  int x = 0, z = FPMake(250);

  while (1)
  {
    engine.clear();

    rotX += (getXAxis() / 200) * 200;
    rotY += (getYAxis() / 200) * 200;

    z -= getButtonState(INPUT_A) ? ONE * 10 : 0;
    z += getButtonState(INPUT_Y) ? ONE * 10 : 0;
    x -= getButtonState(INPUT_X) ? ONE * 10 : 0;
    x += getButtonState(INPUT_B) ? ONE * 10 : 0;

    drawBox(x, 0, z, rotX, rotY);

    drawFPNumber(0, 0, rotX);
    drawFPNumber(0, 16, rotY);

    drawFPNumber(0, 48, x);
    drawFPNumber(0, 64, z);

    engine.drawWindow();
    sync();
  }
}