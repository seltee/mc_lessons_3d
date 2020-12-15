#include "f_math.h"
#include "m_math.h"

// Max polygons on the screen
// May be much more overall in objects, but this is the maximum that may be after culling operations
#define MAX_POLYGONS 100

// This ones describes geometry, that will be used in the object
struct Mesh{
  const int *vertex;
  const unsigned int *polygons;
  unsigned int polyCount;
};

// This ones defines object. Mesh - is geometry to use, another are position, rotation and scale
struct Object{
  Mesh *mesh;
  int FPPositionX, FPPositionY, FPPositionZ;
  int FPRotationX, FPRotationY, FPRotationZ;
  int FPScale;
};

void EngineInit(int maxObjects);

// This ones creates an object and add it to render array
Object *EngineCreateObject(Mesh *mesh);

// Creates an object with existing box geometry
Object *EngineCreateBox(int size);

void EngineDrawScreen();
void EngineMakePolygonList();
void EngineSortPolygonList();
