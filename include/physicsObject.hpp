#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <glm/glm.hpp>
#include "collider.hpp"

class BoundingSphere;

class PhysicsObject
{
public:
  PhysicsObject(const glm::vec3& pos, const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable = true);

  PhysicsObject() = default;
  ~PhysicsObject() = default;

  glm::vec3 getPos() const { return m_pos; }
  glm::vec3 getVel() const { return m_vel; }
  glm::vec3 getAcc() const { return m_acc; }
  float getMass() const { return m_mass; }
  float getInvMass() const { return m_inv_mass; }
  Collider* getCollider();

  void setPos(const glm::vec3& pos);
  void setVel(const glm::vec3& vel) { m_vel = vel; }
  void setAcc(const glm::vec3& acc) { m_acc = acc; }
  void setMass(const float& mass)   { m_mass = mass; m_inv_mass = 1/mass; }
  void setCollider(Collider* collider);

  bool isMovable() const { return m_movable; }
  void setMovable(const bool& movable) { m_movable = movable; }
  void update(float delta);

  glm::vec3 convertFromMPerSec(const glm::vec3 v);
  glm::vec3 convertFromMPerSec2(const glm::vec3 v);

  void test() const;

private:
  glm::vec3 m_pos;
  glm::vec3 m_vel;
  glm::vec3 m_acc;
  float m_mass;
  float m_inv_mass;

  Collider* m_collider; 

  bool m_movable;
};

#endif // PHYSICS_OBJECT_H
