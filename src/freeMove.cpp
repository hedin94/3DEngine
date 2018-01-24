#include "freeMove.hpp"

FreeMove::
FreeMove(float speed, float speedMod, Uint8 speedModKey, Uint8 forward, Uint8 backward, Uint8 right, Uint8 left)
  : m_speed(speed), m_speedMod(speedMod), m_speedModKey(speedModKey), m_forward(forward), m_backward(backward), m_right(right), m_left(left) {}

FreeMove::
~FreeMove()
{
}

void
FreeMove::
input(float delta)
{
  float amount = m_speed * delta;

  if(Input::get_downKey(m_speedModKey))
    amount *= m_speedMod;

  if(Input::get_downKey(m_forward))
    move(getTransform()->getForward(), amount);

  if(Input::get_downKey(m_backward))
    move(getTransform()->getBackward(), amount);

  if(Input::get_downKey(m_left))
    move(getTransform()->getRight(), amount);

  if(Input::get_downKey(m_right))
    move(getTransform()->getLeft(), amount);


  if(Input::get_downKey(SDLK_SPACE))
    move(getTransform()->getUp(), amount);

  if(Input::get_downKey(SDLK_LCTRL))
    move(getTransform()->getDown(), amount);
  
}

void
FreeMove::
setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}

void
FreeMove::
move(glm::vec3 direction, float amount)
{
  getTransform()->getPos() += direction * amount;
}
