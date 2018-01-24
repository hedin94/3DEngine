#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

class Camera;

class Transform
{
public:
  Transform(const glm::vec3& pos = glm::vec3(0,0,0), const glm::quat& rot = glm::quat(1.0f,0.0f,0.0f,0.0f), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f) )
    : m_pos(pos), m_rot(rot), m_scale(scale), m_parent(nullptr) {}
  virtual ~Transform();
  
  glm::mat4 getModel() const;
  glm::mat4 getMVP(const Camera* camera);
  glm::mat4 getMVP(const Camera* camera) const;

  void rotate(const float& angle, const glm::vec3& axis);
  void rotate(glm::quat rotation);

  glm::vec3 getRight();
  glm::vec3 getLeft();
  glm::vec3 getUp();
  glm::vec3 getDown();
  glm::vec3 getForward();
  glm::vec3 getBackward();

  glm::vec3& getPos() { return m_pos; }
  glm::quat& getRot() { return m_rot; }
  glm::vec3& getScale() { return m_scale; }

  glm::vec3 getTransformedPos();
  glm::quat getTransformedRot(); 

  void lookAt(glm::vec3 point, glm::vec3 up);
  glm::quat getLookAtRot(glm::vec3 point, glm::vec3 up);

  void setPos(const glm::vec3& pos) { m_pos = pos; } 
  void setRot(const glm::quat& rot);
  void setScale(const glm::vec3& scale) { m_scale = scale; }

  void setParent(Transform* parent) { m_parent = parent; }

  bool hasChanged() const;
  void update();

private:
  glm::vec3 m_pos{ glm::vec3() };
  glm::quat m_rot{ glm::quat() };
  glm::vec3 m_scale{ glm::vec3() };

  glm::vec3 m_oldPos{ glm::vec3(1,1,1) };
  glm::quat m_oldRot{ glm::quat(0,0,0,1) };
  glm::vec3 m_oldScale{ glm::vec3(1,1,1) };

  Transform* m_parent;

  glm::mat4 m_parentMatrix{glm::mat4()};

  glm::vec3 rotate(glm::vec3 v, glm::quat q);
  glm::quat mul(glm::quat q, glm::vec3 v);
  glm::mat4 translate(const glm::vec3& v) const;
  glm::mat4 scale(const glm::vec3& v) const;
};
#endif // TRANSFORM_H
