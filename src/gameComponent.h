#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "renderingEngine.h"
#include "coreEngine.h"
#include "gameObject.h"
#include "transform.h"
#include "debug.h"

class GameObject;
class RenderingEngine;
class CoreEngine;
class Shader;

class GameComponent
{
public:
  GameComponent();
  virtual ~GameComponent();

  virtual void input(float delta) = 0;
  virtual void update(float delta) = 0;
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) = 0;

  virtual void addToEngine(CoreEngine* engine) { DEBUG("GameComponent::addToEngine");}

  virtual void setParent(GameObject* parent);
  Transform* getTransform();

protected:
  GameObject* m_parent;
};
#endif // GAME_COMPONENT_H
