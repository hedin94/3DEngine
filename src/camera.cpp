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
  Transform* t = getTransform();
  return m_perspective * glm::lookAt(t->getPos(), t->getPos() + t->getForward(), t->getUp());
}

glm::mat4 Camera::getViewProjection() const
{
  Transform* t = getTransform(); 
  return m_perspective * glm::lookAt(t->getPos(), t->getPos() + t->getForward(), t->getUp());
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
  engine->getRenderingEngine()->setCamera(m_camera);
}

void
CameraComponent::
setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
  m_camera->setTransform(parent->getTransform());
}

void
CameraComponent::
update(float delta){
}

std::string
CameraComponent::
str() const {
    return "CameraComponent";
}
