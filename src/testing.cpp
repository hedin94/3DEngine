#include "testing.hpp"
#include "boundingSphere.hpp"
#include "boundingBox.hpp"
#include "plane.hpp"
#include "physicsObject.hpp"
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
