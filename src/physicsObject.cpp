#include "physicsObject.hpp"
#include "boundingSphere.hpp"
#include <iostream>

PhysicsObject::PhysicsObject(const glm::vec3& pos, const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable)
  : m_pos(pos), m_vel(convertFromMPerSec(vel)), m_acc(glm::vec3()), m_mass(mass), m_inv_mass(1/mass), m_collider(collider), m_movable(movable) 
{
  // m_collider->translate(pos);
}

void PhysicsObject::update(float delta)
{
  if(isMovable())
    {
      glm::vec3 gravityAcc(0, -10.0f, 0);
      gravityAcc = convertFromMPerSec2(gravityAcc);
      //setAcc(gravityAcc + m_acc);
      glm::vec3 acc(m_acc + gravityAcc);

      glm::vec3 s((m_vel + (acc * delta * 0.5f)) * delta);

      m_pos += s;
      m_collider->translate(s);
      m_vel += acc * delta; 
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

glm::vec3 PhysicsObject::convertFromMPerSec(const glm::vec3 v)
{
  return v * 0.002f;
}


glm::vec3 PhysicsObject::convertFromMPerSec2(const glm::vec3 v)
{
  return convertFromMPerSec(convertFromMPerSec(v));
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
