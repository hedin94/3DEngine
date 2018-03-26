#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "renderingEngine.hpp"
#include "coreEngine.hpp"
#include "gameObject.hpp"
#include "transform.hpp"
#include "debug.hpp"

class GameObject;
class RenderingEngine;
class CoreEngine;
class Shader;

class GameComponent
{
public:
    GameComponent();
    virtual ~GameComponent();

    virtual void input(float delta) = 0;
    virtual void update(float delta) = 0;
    virtual void render(Shader* shader, RenderingEngine* renderingEngine) = 0;

    virtual void addToEngine(CoreEngine* engine) { DEBUG("GameComponent::addToEngine");}

    virtual void setParent(GameObject* parent);
    Transform* getTransform();

    virtual std::string str() const;

protected:
    GameObject* m_parent;
};
#endif // GAME_COMPONENT_H
