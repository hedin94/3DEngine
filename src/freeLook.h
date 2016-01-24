#ifndef FREE_LOOK_H
#define FREE_LOOK_H

#include "gameComponent.h"
#include <SDL.h>

class FreeLook : public GameComponent
{
public:
  FreeLook(float sensitivity = 1.0f, Uint8 unlockMouseKey = SDL_BUTTON_LEFT);
  virtual ~FreeLook();

  virtual void input(float delta) override;
  virtual void update(float delta) override {}
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) override {}

  virtual void setParent(GameObject* parent) override;

private:
  float m_sensitivity;
  Uint8 m_unlockMouseKey;
  bool m_mouseLocked;
};

#endif // FREE_LOOK_H
