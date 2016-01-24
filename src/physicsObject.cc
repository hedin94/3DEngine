#include "physicsObject.h"
#include "boundingSphere.h"
#include <iostream>

PhysicsObject::PhysicsObject(const glm::vec3& pos, const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable)
  : m_pos(pos), m_vel(vel), m_mass(mass), m_collider(collider), m_movable(movable) 
{
  // m_collider->translate(pos);
}

void PhysicsObject::update(float delta)
{
  if(m_movable)
    {
      m_pos += m_vel * delta;
      m_collider->translate(m_vel * delta);
    }
}

void PhysicsObject::setPos(const glm::vec3& pos)
{
  m_pos = pos;
  auto bs = dynamic_cast<BoundingSphere*>(m_collider);
  if(bs != nullptr)
    bs->setPos(pos);
}
Collider* PhysicsObject::getCollider()
{
  return m_collider;
}

void PhysicsObject::setCollider(Collider* collider) 
{ 
  m_collider = collider; 
}

void PhysicsObject::test() const
{
  std::cout << "TEST: PhysicsObject\t";
  // PhysicsObject po(glm::vec3(), glm::vec3(1,2,0), 1, new Collider());
  
  // glm::vec3 startPos = po.getPos();
  // glm::vec3 vel = po.getVel();
  // po.update(10);
  // glm::vec3 endPos = po.getPos();

  // assert(endPos == glm::vec3(10, 20, 0));
  std::cout << "SUCCESS" << std::endl;
}
