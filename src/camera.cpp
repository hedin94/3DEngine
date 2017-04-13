#include <SDL.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/ext.hpp>
#include "debug.hpp"
#include "camera.hpp"
#include "constants.hpp"

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

void
CameraComponent::
update(float delta){
  // auto t = getTransform();
  // auto mvp = t->getMVP(m_camera);
  // std::cout << "rot: " << glm::to_string(t->get_rot())
  // 	    << "\nmvp: " << glm::to_string(mvp) << std::endl;
}
