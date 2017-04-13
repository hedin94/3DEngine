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
  glm::quat lookAtRot = getTransform()->get_lookAt_rot(m_objectToFollow->getTransform()->get_transformed_pos(), 
							glm:: vec3(0,1,0));
  glm::quat newRot = glm::lerp(getTransform()->get_rot(), lookAtRot, 0.1f);
  getTransform()->set_rot(newRot);


  // Move towards/away from object
  glm::vec3 currentPosition = getTransform()->get_transformed_pos();
  glm::vec3 objectPosition = m_objectToFollow->getTransform()->get_transformed_pos();

  float distanceToObject = glm::distance(currentPosition, objectPosition);
  glm::vec3 direction = glm::normalize(objectPosition - currentPosition);
  getTransform()->set_pos(currentPosition + ((distanceToObject - m_distance) * direction));
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
