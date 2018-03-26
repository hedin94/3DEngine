#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "gameComponent.hpp"
#include "coreEngine.hpp"
#include "renderingEngine.hpp"
#include "transform.hpp"
#include "shader.hpp"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class GameComponent;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();

    GameObject* addChild(GameObject* child);
    GameObject* addComponent(GameComponent* component);
    void setEngine(CoreEngine* engine);

    void input(float delta);
    void update(float delta);
    void render(Shader* shader, RenderingEngine* renderingEngine);

    void inputAll(float delta);
    void updateAll(float delta);
    void renderAll(Shader* shader, RenderingEngine* renderingEngine);

    Transform* getTransform() { return m_transform; }
    void       setTransform(Transform* transform) { m_transform = transform; }
    std::vector<GameObject*> getAttached();

    GameObject* getRoot();
    GameObject* getParent() const { return m_parent; }
    void        setParent(GameObject* parent) { m_parent = parent; }

    void dumpComponents() const;

private:
    GameObject* m_parent;
    std::vector<GameObject*> m_children;
    std::vector<GameComponent*> m_components;
    Transform* m_transform;
    CoreEngine* m_engine;
};

#endif // GAME_OBJECT_H
