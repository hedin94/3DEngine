#ifndef CAMERA_H
#define CAMERA_H

#include "gameComponent.hpp"
#include "input.hpp"
#include "window.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

class Transform;

class Camera
{
public:
  //  Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar, float baseVel = 0.1f, glm::vec3 speed = glm::vec3(0.0f,0.0f,0.0f));
  Camera(const glm::mat4& perspective, Transform* transform)
    : m_perspective{perspective}, m_transform{transform} {}

  virtual ~Camera();
  
  glm::mat4 getViewProjection();
  glm::mat4 getViewProjection() const;

  Transform* getTransform() { return m_transform; }
  Transform* getTransform() const { return m_transform; } 
  void       setTransform(Transform* transform) { m_transform = transform; }

  void setPerspective(const glm::mat4& perspective) { m_perspective = perspective; }


private:

  glm::mat4 m_perspective; // projection
  Transform* m_transform;

};


class CameraComponent : public GameComponent
{
public:
  CameraComponent(const glm::mat4& perspective);

  ~CameraComponent() = default;

  virtual void addToEngine(CoreEngine* engine) override;

  void input(float) {}
  void update(float);
  void render(Shader*, RenderingEngine*) {}

  glm::mat4 getViewProjection() { return m_camera->getViewProjection(); }
  glm::mat4 getViewProjection() const { return m_camera->getViewProjection(); }

  void setPerspective(const glm::mat4& perspective) { m_camera->setPerspective(perspective); }
  virtual void setParent(GameObject* parent) override;

private:
  Camera* m_camera;
};

#endif // CAMERA_H
