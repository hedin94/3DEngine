#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include "physicsObject.hpp"
#include <vector>

class IntersectData;

class PhysicsEngine
{
public:
  PhysicsEngine();
  ~PhysicsEngine();

  PhysicsEngine* addObject(PhysicsObject* object);
  void simulate(const float& delta);
  void handleCollision(const float& delta);

private:
  void printVelocity();
  void printMomentum();

  std::vector<PhysicsObject*> m_objects;
};

#endif // PHYSICS_ENGINE_H
