#ifndef SPAWNER_H
#define SPAWNER_H

#include "gameComponent.h"
#include <SDL.h>

class Spawner : public GameComponent
{
public:
  Spawner(Game* game, Uint8 spawnKey = SDLK_f);
  virtual ~Spawner();

  virtual void input(float delta) override;
  virtual void update(float delta) {}
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) {}

private:
  void spawn(glm::vec3 pos, glm::vec3 vel);

  Uint8 m_spawnKey;
  Game* m_game;
  bool m_spawning = false;
};

#endif // SPAWNER_H
