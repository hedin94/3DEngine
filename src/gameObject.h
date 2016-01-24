#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "gameComponent.h"
#include "coreEngine.h"
#include "renderingEngine.h"
#include "transform.h"
#include "shader.h"
//#include "phongShader.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class GameComponent;

class GameObject
{
public:
  GameObject(const glm::vec3& pos = glm::vec3(0,0,0), const glm::quat& rot = glm::quat(1.0f,0.0f,0.0f,0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f));

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

private:
  std::vector<GameObject*> m_children;
  std::vector<GameComponent*> m_components;
  Transform* m_transform;
  CoreEngine* m_engine;
};

#endif // GAME_OBJECT_H
