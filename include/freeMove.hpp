#ifndef FREE_MOVE_H
#define FREE_MOVE_H

#include "gameComponent.hpp"
#include <SDL.h>
#include <glm/glm.hpp>

class FreeMove : public GameComponent
{
public:
  FreeMove(float speed = 1.0f, float speedMod = 1.0f, Uint8 speedModKey = SDLK_LSHIFT, Uint8 forward = SDLK_w, Uint8 backward = SDLK_s, Uint8 right = SDLK_d, Uint8 left = SDLK_a);
  ~FreeMove();

  virtual void input(float delta) override;
  virtual void update(float delta) {}
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) {}

  virtual void setParent(GameObject* parent) override;

  void move(glm::vec3 direction, float amount);

private:
  float m_speed;
  float m_speedMod;
  
  Uint8 m_speedModKey;
  Uint8 m_forward;
  Uint8 m_backward;
  Uint8 m_right;
  Uint8 m_left;
};

#endif // FREE_MOVE_H
