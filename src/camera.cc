#include "SDL.h"
#include "camera.h"
//#include <cmath>
#include "constants.h"
#include <glm/gtx/rotate_vector.hpp>
#include "debug.h"

//using namespace constants;

// Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, float baseVel, glm::vec3 speed)
// {
//   m_perspective = glm::perspective(fov, aspect, zNear, zFar);
//   m_pos = pos;
//   m_forward = glm::vec3(0,0,1);
//   m_up = glm::vec3(0,1,0);
//   m_right = glm::vec3(1,0,0);
//   m_baseVel = baseVel;  
//   m_speed = speed;
// }


Camera::~Camera()
{
}

glm::mat4 Camera::getViewProjection()
{
  //std::cout << "Camera::getviewProjection" << std::endl;
  Transform* t = getTransform();
  return m_perspective * glm::lookAt(t->get_pos(), t->get_pos() + t->get_forward(), t->get_up());
}

glm::mat4 Camera::getViewProjection() const
{
  //DEBUG("Camera::getviewProjection const");
  Transform* t = getTransform(); 
  return m_perspective * glm::lookAt(t->get_pos(), t->get_pos() + t->get_forward(), t->get_up());
}


/*
 * GameComponent 
 */


CameraComponent::
CameraComponent(const glm::mat4& projection)
{
  m_camera = new Camera(projection, nullptr);
}

void
CameraComponent::
addToEngine(CoreEngine* engine)
{
  //DEBUG("CameraComponent::addToEngine");
  engine->getRenderingEngine()->setCamera(m_camera);
}

void
CameraComponent::
setParent(GameObject* parent)
{
  //DEBUG("CameraComponent::setParent");
  GameComponent::setParent(parent);
  m_camera->setTransform(parent->getTransform());
}
