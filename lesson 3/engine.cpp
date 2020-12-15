#include "engine.h"
#include "../tools/core.h"

int projectionMatrix[16];
int dumpMatrix[16];
int modelMatrix[16];
int viewModelMatrix[16];
int moveMatrix[16];
int scaleMatrix[16];
int rotateMatrix[16];

struct RenderPolygon
{
  int p1[2];
  int p2[2];
  int p3[2];
  short int color;
  short int startX;
  short int endX;
  short int startY;
  short int endY;
  short int zIndex;
  short int shade;
  short int unused;
};

// Position ob cube points
const int cubeVertex[] = {
    HALF, HALF, HALF,
    HALF, HALF, -HALF,
    -HALF, HALF, -HALF,
    -HALF, HALF, HALF,
    HALF, -HALF, HALF,
    HALF, -HALF, -HALF,
    -HALF, -HALF, -HALF,
    -HALF, -HALF, HALF};

const int sunVector[] = {0, 0, ONE};

// Connection with cube point to make triangles. 12 triangles makes 6 quads of which cube consists
const unsigned int cubePolygons[] = {
    0,
    2,
    1,
    0xEFBB,
    0,
    3,
    2,
    0xEFBB,
    4,
    5,
    6,
    0x182B,
    4,
    6,
    7,
    0x182B,
    0,
    1,
    5,
    0x272E,
    0,
    5,
    4,
    0x272E,
    2,
    3,
    7,
    0xEBDE,
    2,
    7,
    6,
    0xEBDE,
    0,
    4,
    7,
    0x18C3,
    0,
    7,
    3,
    0x18C3,
    1,
    2,
    5,
    0xFCA6,
    2,
    6,
    5,
    0xFCA6,
};

Object *engineObjects;
int engineObjectsCount, engineMaxObjects;

int renderPolygonsCount;
RenderPolygon renderPolygongs[MAX_POLYGONS];
RenderPolygon *renderPolygonOrder[MAX_POLYGONS];

Mesh cube;

void lineDrawer(unsigned short *data, unsigned short lNumber)
{
  memset(data, 0, 640);

  short int color;
  short int color2;
  int dot, end;
  int *p1, *p2, *p3;
  int p[2];
  p[1] = lNumber;

  for (int i = 0; i < renderPolygonsCount; i++)
  {
    RenderPolygon *pol = renderPolygonOrder[i];
    if (lNumber >= pol->startY && lNumber <= pol->endY)
    {
      color = pol->color;
      dot = pol->startX;
      end = pol->endX;
      p1 = pol->p1;
      p2 = pol->p2;
      p3 = pol->p3;

      int py2mp1y = p2[1] - p1[1];
      int py3mp2y = p3[1] - p2[1];
      int py1mp3y = p1[1] - p3[1];

      int px2mp1x = p2[0] - p1[0];

      int mr1 = (p[1] - p1[1]) * (p2[0] - p1[0]);
      int mr2 = (p[1] - p2[1]) * (p3[0] - p2[0]);
      int mr3 = (p[1] - p3[1]) * (p1[0] - p3[0]);

      for (; dot < end; dot++)
      {
        p[0] = dot;

        if (((p[0] - p1[0]) * py2mp1y - mr1) < 0)
          continue;

        if (((p[0] - p2[0]) * py3mp2y - mr2) < 0)
          continue;

        if (((p[0] - p3[0]) * py1mp3y - mr3) < 0)
          continue;

        data[dot] = color;
      }
    }
  }
}

void EngineInit(int maxObjects)
{
  engineObjects = (Object *)malloc(sizeof(Object) * maxObjects);
  engineObjectsCount = 0;
  engineMaxObjects = maxObjects;

  setSpriteLimit(40);
  setFPS(30);

  MPerspective(projectionMatrix);
  setPreProcessCallback(lineDrawer);

  cube.polyCount = 12;
  cube.polygons = cubePolygons;
  cube.vertex = cubeVertex;
}

Object *EngineCreateObject(Mesh *mesh)
{
  if (engineObjectsCount < engineMaxObjects)
  {
    Object *out = &engineObjects[engineObjectsCount];
    memset(out, 0, sizeof(Object));
    out->mesh = mesh;
    out->FPScale = FPMake(1);

    engineObjectsCount++;
    return out;
  }
  return nullptr;
}

Object *EngineCreateBox(int size)
{
  return EngineCreateObject(&cube);
}

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

void EngineDrawScreen()
{
  EngineMakePolygonList();
  EngineSortPolygonList();

  sync();
}

void EngineMakePolygonList()
{
  renderPolygonsCount = 0;

  int s1[4], s2[4], s3[4];
  unsigned int r, g, b;

  for (int o = 0; o < engineObjectsCount; o++)
  {
    Object *obj = &engineObjects[o];

    int px = obj->FPPositionX;
    int py = obj->FPPositionY;
    int pz = obj->FPPositionZ;

    MTransition(moveMatrix, px, py, pz);
    MScale(scaleMatrix, obj->FPScale, obj->FPScale, obj->FPScale);
    MIdentity(modelMatrix);

    if (obj->FPRotationX)
    {
      MRotationX(rotateMatrix, obj->FPRotationX);
      MMultiply(rotateMatrix, modelMatrix, dumpMatrix);
      MCopy(dumpMatrix, modelMatrix);
    }

    if (obj->FPRotationY)
    {
      MRotationY(rotateMatrix, obj->FPRotationY);
      MMultiply(rotateMatrix, modelMatrix, dumpMatrix);
      MCopy(dumpMatrix, modelMatrix);
    }

    if (obj->FPRotationX)
    {
      MRotationZ(rotateMatrix, obj->FPRotationZ);
      MMultiply(rotateMatrix, modelMatrix, dumpMatrix);
      MCopy(dumpMatrix, modelMatrix);
    }

    MMultiply(moveMatrix, modelMatrix, dumpMatrix);
    MMultiply(scaleMatrix, dumpMatrix, modelMatrix);
    MMultiply(projectionMatrix, modelMatrix, viewModelMatrix);

    Mesh *mesh = obj->mesh;
    int polyCount = mesh->polyCount;

    for (int i = 0; i < polyCount; i++)
    {
      // Numbers of polygons
      int c = i * 4;
      int pv1 = mesh->polygons[c];
      int pv2 = mesh->polygons[c + 1];
      int pv3 = mesh->polygons[c + 2];
      int color = mesh->polygons[c + 3];

      // Polygons
      const int *v1 = &mesh->vertex[pv1 * 3];
      const int *v2 = &mesh->vertex[pv2 * 3];
      const int *v3 = &mesh->vertex[pv3 * 3];

      // Point on screen plus Z
      projectPoint(viewModelMatrix, v1, s1);
      projectPoint(viewModelMatrix, v2, s2);
      projectPoint(viewModelMatrix, v3, s3);

      // Backface Cooling
      int n[3];
      int camera[3] = {-s1[0], -s1[1], -s1[2]};

      FPGetNormal(s1, s2, s3, n);
      int dProduct = FPDotProduct(n, camera);

      if (i == 0)
      {
        char s[8];
        itoa(dProduct, s);
      }

      if (dProduct >= 0)
      {
        continue;
      }

      // Position of points on real screen
      int n1x = FPFloor(FPDivide(s1[0] * 160, s1[2])) + 160;
      int n1y = FPFloor(-FPDivide(s1[1] * 160, s1[2])) + 120;
      int n2x = FPFloor(FPDivide(s2[0] * 160, s2[2])) + 160;
      int n2y = FPFloor(-FPDivide(s2[1] * 160, s2[2])) + 120;
      int n3x = FPFloor(FPDivide(s3[0] * 160, s3[2])) + 160;
      int n3y = FPFloor(-FPDivide(s3[1] * 160, s3[2])) + 120;

      // Crop
      int startX = min3(n1x, n2x, n3x);
      int endX = max3(n1x, n2x, n3x);

      if (startX >= 320)
        continue;
      if (endX < 0)
        continue;
      if (startX < 0)
        startX = 0;
      if (endX >= 320)
        endX = 319;

      int startY = min3(n1y, n2y, n3y);
      int endY = max3(n1y, n2y, n3y);
      if (startY < 0)
        startY = 0;
      if (startY >= 240)
        continue;
      if (endY < 0)
        continue;
      if (endY >= 240)
        endY = 239;

      // Rendering information
      renderPolygongs[renderPolygonsCount].p1[0] = n1x;
      renderPolygongs[renderPolygonsCount].p1[1] = n1y;
      renderPolygongs[renderPolygonsCount].p2[0] = n2x;
      renderPolygongs[renderPolygonsCount].p2[1] = n2y;
      renderPolygongs[renderPolygonsCount].p3[0] = n3x;
      renderPolygongs[renderPolygonsCount].p3[1] = n3y;

      //Shading
      int unitN[3];
      FPGetUnitVector(n, unitN);
      dProduct = FPDotProduct(sunVector, unitN);

      int colorMultiplier = dProduct > 0 ? FPMultiply(dProduct, (ONE * 3) / 4) + ONE / 4: ONE / 4;
      unsigned short colorShort = color;
      r = ((int)((colorShort >> 3) & 0x1f)) << FSHIFT;
      g = ((int)((colorShort >> 13) + ((color & 0x07) << 3))) << FSHIFT;
      b = ((int)((colorShort >> 8) & 0x1f)) << FSHIFT;
      r = FPMultiply(colorMultiplier, r) >> FSHIFT;
      g = FPMultiply(colorMultiplier, g) >> FSHIFT;
      b = FPMultiply(colorMultiplier, b) >> FSHIFT;
      color = (r << 3) + (g >> 3) + (g << 13) + (b << 8);

      renderPolygongs[renderPolygonsCount].color = color;

      renderPolygongs[renderPolygonsCount].startX = startX;
      renderPolygongs[renderPolygonsCount].endX = endX;
      renderPolygongs[renderPolygonsCount].startY = startY;
      renderPolygongs[renderPolygonsCount].endY = endY;
      renderPolygongs[renderPolygonsCount].zIndex = FPDivide((s1[2] + s2[2] + s3[2]), 3 << FSHIFT);

      renderPolygonOrder[renderPolygonsCount] = &renderPolygongs[renderPolygonsCount];

      renderPolygonsCount++;
    }
  }
}

void EngineSortPolygonList()
{
  bool changed = true;
  RenderPolygon *p;

  while (changed)
  {
    changed = false;
    for (int i = 1; i < renderPolygonsCount; i++)
    {
      if (renderPolygonOrder[i - 1]->zIndex < renderPolygonOrder[i]->zIndex)
      {
        changed = true;
        p = renderPolygonOrder[i - 1];
        renderPolygonOrder[i - 1] = renderPolygonOrder[i];
        renderPolygonOrder[i] = p;
      }
    }
  }
}