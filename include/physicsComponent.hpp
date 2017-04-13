#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "gameComponent.hpp"
#include "collider.hpp"

class PhysicsObject;
class CoreEngine;
class BoundingSphere;

class PhysicsComponent : public GameComponent
{
public:
  PhysicsComponent(const glm::vec3& vel, const float& mass, Collider* collider, const bool& movable = true);
  ~PhysicsComponent();

  virtual void input(float delta) override {} 
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) override {}
  virtual void update(float delta) override;

  void addToEngine(CoreEngine* engine) override;
  void setParent(GameObject* parent) override;

  PhysicsObject* getObject() const { return m_physicsObject; }

private:
  PhysicsObject* m_physicsObject;
};

#endif // PHYSICS_COMPONENT_H
