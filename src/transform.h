#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
//#include "camera.h"

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

  glm::vec3 get_right();
  glm::vec3 get_left();
  glm::vec3 get_up();
  glm::vec3 get_down();
  glm::vec3 get_forward();
  glm::vec3 get_backward();

  glm::vec3& get_pos() { return m_pos; }
  glm::quat& get_rot() { return m_rot; }
  glm::vec3& get_scale() { return m_scale; }

  glm::vec3 get_transformed_pos();
  glm::quat get_transformed_rot(); 

  void lookAt(glm::vec3 point, glm::vec3 up);
  glm::quat get_lookAt_rot(glm::vec3 point, glm::vec3 up);

  void set_pos(const glm::vec3& pos) { m_pos = pos; } 
  void set_rot(const glm::quat& rot);
  void set_scale(const glm::vec3& scale) { m_scale = scale; }

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
