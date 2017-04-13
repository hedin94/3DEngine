#include "gameComponent.hpp"

GameComponent::GameComponent()
{
  m_parent = nullptr;
}

GameComponent::~GameComponent()
{
}

void GameComponent::setParent(GameObject* parent)
{
  DEBUG("GameComponent::setParent");
  m_parent = parent;
}

Transform* GameComponent::getTransform()
{
  return m_parent->getTransform();
}
