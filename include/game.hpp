#ifndef GAME_H
#define GAME_H

#include "renderingEngine.hpp"
#include "coreEngine.hpp"
#include "gameObject.hpp"

class RenderingEngine;
class CoreEngine;
class GameObject;

class Game
{
 public:
  Game();
  virtual ~Game();

  virtual void init() = 0;
  void input(float delta);
  void update(float delta);
  void render(RenderingEngine* renderingEngine);

  GameObject* getRootObject();
  void setEngine(CoreEngine* engine);

protected:
  void addToScene(GameObject* child);

 private:
  GameObject* m_root;
};

#endif // GAME_H
