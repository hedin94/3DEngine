#ifndef FOLLOW_COMPONENT_H
#define FOLLOW_COMPONENT_H

/******************************************************************
 * FollowComponent 
 *
 * This component will make a GameObject follow another GameObject
 * and will always keep the specified distance
 ******************************************************************/

#include "renderingEngine.h"
#include "coreEngine.h"
#include "gameObject.h"
#include "transform.h"
#include "gameComponent.h"
#include "debug.h"

class GameObject;
class RenderingEngine;
class CoreEngine;
class Shader;

class FollowComponent : public GameComponent
{
public:
  FollowComponent(const float& distance, GameObject* objectToFollow);
  virtual ~FollowComponent();

  virtual void input(float delta) {}
  virtual void update(float delta);
  virtual void render(Shader* shader, RenderingEngine* renderingEngine);

  virtual void addToEngine(CoreEngine* engine);

  virtual void setParent(GameObject* parent);

private:

  float m_distance;
  GameObject* m_objectToFollow;
  glm::vec3 m_currentPos;
  glm::vec3 m_nextPos;

};
#endif // FOLLOW_COMPONENT_H
