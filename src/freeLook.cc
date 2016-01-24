#include "freeLook.h"
#include "glm/glm.hpp"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>

glm::quat mul(glm::quat quat, glm::vec3 vec);

FreeLook::FreeLook(float sensitivity, Uint8 unlockMouseKey)
  : m_sensitivity(sensitivity), m_unlockMouseKey(unlockMouseKey), m_mouseLocked(false) {}

FreeLook::~FreeLook()
{
}

void FreeLook::input(float delta)
{
  glm::vec2 center = Window::get_windowCenter();

  if(Input::get_downMouseButton(m_unlockMouseKey))
    {
      SDL_ShowCursor(0);
      m_mouseLocked = true;
      SDL_WarpMouseInWindow(Window::get_window(), center.x, center.y);
      Input::set_mouseX(center.x);
      Input::set_mouseY(center.y);
    }

  if(Input::get_upMouseButton(m_unlockMouseKey))
    {
      m_mouseLocked = false;
      SDL_ShowCursor(1);
    }

  if(m_mouseLocked)
    {
      int rotX = Input::get_mouseX() - center.x;
      int rotY = Input::get_mouseY() - center.y;
      
      if(rotY)
       	getTransform()->rotate(rotY * m_sensitivity, getTransform()->get_right());

      if(rotX)
      	getTransform()->rotate((-rotX) * m_sensitivity, glm::vec3(0,1,0));
      

      if(rotX != 0 || rotY != 0)
	SDL_WarpMouseInWindow(Window::get_window(), center.x, center.y);
    }

  //get_speed().x = 0.0f;
  //get_speed().y = 0.0f;
  //get_speed().z = 0.0f;

  //float velMod = 1.0f;

  /*if(Input::get_downKey(SDLK_LSHIFT))
    {
    velMod = 2.0f;
    }

    if(Input::get_downKey(SDLK_a))
    {
    get_speed().x += m_baseVel * velMod;
    }
    if(Input::get_downKey(SDLK_d))
    {
    get_speed().x -= m_baseVel * velMod;
    }

    if(Input::get_downKey(SDLK_w))
    {
    get_speed().z += m_baseVel * velMod;
    }
    if(Input::get_downKey(SDLK_s))
    {
    get_speed().z -= m_baseVel * velMod;
    }
    if(Input::get_downKey(SDLK_SPACE))
    {
    get_speed().y += m_baseVel * velMod;
    }
    if(Input::get_downKey(SDLK_LCTRL))
    {
    get_speed().y -= m_baseVel * velMod;
    }

    moveForward();
    moveUp();
    strafeRight();*/
}

void
FreeLook::
setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}

glm::quat mul(glm::quat quat, glm::vec3 vec)
{
  float w = -quat.x * vec.x - quat.y * vec.y - quat.z * vec.z;
  float x =  quat.w * vec.x + quat.y * vec.z - quat.z * vec.y;
  float y =  quat.w * vec.y + quat.z * vec.x - quat.x * vec.z;
  float z =  quat.w * vec.z + quat.x * vec.y - quat.y * vec.x;

  return glm::quat(w, x, y, z);
}
