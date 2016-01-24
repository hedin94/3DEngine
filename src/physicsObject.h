#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <glm/glm.hpp>
//#include "boundingSphere.h"
#include "collider.h"

class BoundingSphere;

class PhysicsObject
{
public:
  PhysicsObject(const glm::vec3& pos, const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable = true);

  PhysicsObject() = default;
  ~PhysicsObject() = default;

  glm::vec3 getPos() const { return m_pos; }
  glm::vec3 getVel() const { return m_vel; }
  float getMass() const { return m_mass; }
  Collider* getCollider();

  void setPos(const glm::vec3& pos);
  void setVel(const glm::vec3& vel) { m_vel = vel; }
  void setMass(const float& mass)   { m_mass = mass; }
  void setCollider(Collider* collider);

  bool isMovable() const { return m_movable; }
  void setMovable(const bool& movable) { m_movable = movable; }
  void update(float delta);

  void test() const;

private:
  glm::vec3 m_pos;
  glm::vec3 m_vel;
  float m_mass;

  Collider* m_collider; 

  bool m_movable;
};

#endif // PHYSICS_OBJECT_H
