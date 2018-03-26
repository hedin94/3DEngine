#include "gameObject.hpp"
#include "debug.hpp"

#include <iterator>
#include <algorithm>
#include <iostream>

GameObject::
GameObject() {
    m_parent = nullptr;
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
    child->setParent(this);
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
	}

    result.push_back(this);

    return result;
}

GameObject*
GameObject::
getRoot()
{
    if (!m_parent) return this;
    return m_parent->getRoot();
}


void
GameObject::
dumpComponents() const {
    std::cout << "Dump components of game object:" << std::endl;
    for (auto c : m_components) {
	std::cout << c->str() << std::endl;
    }
}
