#include "engine.h"
#include "utils.h"
#include "f_math.h"
#include "m_math.h"
#include "../tools/core.h"

int main()
{
  sync();
  EngineInit(8);

  // Creating 3 boxes. Polygons and vertices of them is shared between and laying in rom memory. So, each box has only position and orientation in space and scale.
  // It gives us ability with just out 20 kb of RAM to create a lot of boxes!
  Object *box1 = EngineCreateBox(FPMake(1));
  Object *box2 = EngineCreateBox(FPMake(1));
  Object *box3 = EngineCreateBox(FPMake(1));

  // Initial rotation in fixed point
  int rotY = FPMake(0);

  // Setting the position of our boxes. We will only rotate them
  box1->FPPositionZ = FPMake(800);
  box2->FPPositionZ = FPMake(1000);
  box3->FPPositionZ = FPMake(1000);

  box1->FPPositionX = FPMake(300);
  box2->FPPositionX = FPMake(200);
  box3->FPPositionX = -FPMake(500);

  box1->FPPositionY = -FPMake(200);
  box2->FPPositionY = FPMake(400);
  box3->FPPositionY = FPMake(80);

  // Main example loop
  while (1)
  {
    // One is fixed point equalent of 1.0f. You can freely multiply in by integer numbers
    rotY += ONE * 2;

    // Setting the rotation of our boxes
    box1->FPRotationY = rotY;
    box1->FPRotationX = rotY;
    box2->FPRotationY = rotY / 2;
    box3->FPRotationY = rotY / 4;

    // Drawing to the screen
    EngineDrawScreen();
  }
}