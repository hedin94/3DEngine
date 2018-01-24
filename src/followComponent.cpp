#include "followComponent.hpp"
#include "util.hpp"

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

FollowComponent::FollowComponent(const float& distance, GameObject* objectToFollow)
  : m_distance(distance), m_objectToFollow(objectToFollow), m_currentPos(glm::vec3()), m_nextPos(glm::vec3())
{

}

FollowComponent::~FollowComponent()
{
}

void FollowComponent::update(float delta)
{
  // Look at the other object
  glm::quat lookAtRot = getTransform()->getLookAtRot(m_objectToFollow->getTransform()->getTransformedPos(), 
							glm:: vec3(0,1,0));
  glm::quat newRot = glm::lerp(getTransform()->getRot(), lookAtRot, 0.1f);
  getTransform()->setRot(newRot);


  // Move towards/away from object
  glm::vec3 currentPosition = getTransform()->getTransformedPos();
  glm::vec3 objectPosition = m_objectToFollow->getTransform()->getTransformedPos();

  float distanceToObject = glm::distance(currentPosition, objectPosition);
  glm::vec3 direction = glm::normalize(objectPosition - currentPosition);
  getTransform()->setPos(currentPosition + ((distanceToObject - m_distance) * direction));
}

void FollowComponent::render(Shader* shader, RenderingEngine* renderingEngine)
{

}

void FollowComponent::addToEngine(CoreEngine* engine)
{

}

void FollowComponent::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}
