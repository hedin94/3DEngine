#include "testing.h"
#include "boundingSphere.h"
#include "boundingBox.h"
#include "plane.h"
#include "physicsObject.h"
#include <iostream>

using namespace std;

void Testing::runAllTests()
{
  std::cout << "Running all tests\n";

  BoundingSphere bs;
  bs.test();

  BoundingBox bb;
  bb.test();

  Plane plane;
  plane.test();

  PhysicsObject po;
  po.test();

  std::cout << std::endl;
}
