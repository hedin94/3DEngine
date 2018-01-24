#include "gameObject.hpp"
#include "debug.hpp"

#include <iterator>
#include <algorithm>
#include <iostream>

// GameObject::
// GameObject(const glm::vec3& pos, const glm::quat& rot, const glm::vec3& scale)
// {
//   m_transform = new Transform(pos, rot, scale);
//   m_engine = nullptr;
// }

GameObject::
GameObject() {
    m_transform = new Transform();
    m_engine = nullptr;
}

GameObject::
~GameObject()
{
  for(auto component : m_components)
    delete component;

  for(auto child : m_children)
    delete child; 
}

GameObject*
GameObject::
addChild(GameObject* child)
{
  //  DEBUG("GameObject::addChild");

  m_children.push_back(child);
  child->setEngine(m_engine);
  child->getTransform()->setParent(m_transform);
  return this;
}

GameObject* 
GameObject::
addComponent(GameComponent* component)
{
  //DEBUG("GameObject::addComponent");
  ASSERT(component != nullptr, "GameObject::addComponent");

  component->setParent(this);
  m_components.push_back(component);

  return this;
}

void
GameObject::
setEngine(CoreEngine* engine)
{
  DEBUG("GameObject::setEngine");
  if(m_engine != engine)
    {
      m_engine = engine;

      for(auto component : m_components)
	component->addToEngine(engine);

      for(auto child : m_children)
	child->setEngine(engine);
    }
}

void 
GameObject::
input(float delta)
{
  for(auto component : m_components)
    component->input(delta);
}

void 
GameObject::
update(float delta)
{
  //DEBUG("GameObject::update");
  getTransform()->update();

  for(auto component : m_components)
    component->update(delta);
}

void 
GameObject::
render(Shader* shader, RenderingEngine* renderingEngine)
{
  //DEBUG("GameObject::render");
  for(auto component : m_components)
    component->render(shader, renderingEngine);
}


void 
GameObject::
inputAll(float delta)
{
  input(delta);

  for(auto child : m_children)
    child->inputAll(delta);
}

void 
GameObject::
updateAll(float delta)
{
  update(delta);

  for(auto child : m_children)
    child->updateAll(delta);
}

void 
GameObject::
renderAll(Shader* shader, RenderingEngine* renderingEngine)
{
  render(shader, renderingEngine);

  for(auto child : m_children)
    child->renderAll(shader, renderingEngine);
}

std::vector<GameObject*>
GameObject::
getAttached()
{
  std::vector<GameObject*> result;

  for(auto child : m_children)
    {
      copy(child->getAttached().begin(), child->getAttached().end(), back_inserter(result));
      // std::cout << "GameObject::getAttached\tChild components: " << child->m_components.size() << std::endl;
    }
//result.insert(result.end(), child->getAttached().begin(), child->getAttached().end());

  result.push_back(this);

  return result;
}
