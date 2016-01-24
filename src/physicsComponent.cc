#include "physicsComponent.h"
#include "physicsObject.h"
#include "coreEngine.h"
#include "physicsEngine.h"
#include "gameObject.h"
#include "boundingSphere.h"

PhysicsComponent::PhysicsComponent(const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable)
  : m_physicsObject(new PhysicsObject(glm::vec3(), vel, mass, collider, movable))
{
}


PhysicsComponent::~PhysicsComponent()
{
  delete m_physicsObject;
}

void PhysicsComponent::update(float delta)
{
  glm::vec3 newPos =  m_physicsObject->getPos();
  getTransform()->set_pos(newPos);
}

void PhysicsComponent::addToEngine(CoreEngine* engine)
{
  engine->getPhysicsEngine()->addObject(m_physicsObject);
}

void PhysicsComponent::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
  DEBUG("PhysicsComponent::setParent");
  m_physicsObject->setPos(getTransform()->get_pos());
}
