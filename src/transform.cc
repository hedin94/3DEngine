#include "transform.h"
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp> 
#include "camera.h"
#include "debug.h"

glm::vec3 transform(glm::mat4 m, glm::vec3 r);
glm::mat4 initRotation(glm::mat4 m, glm::vec3 forward, glm::vec3 up);
glm::mat4 initRotation(glm::mat4 m, glm::vec3 forward, glm::vec3 up, glm::vec3 right);

Transform::~Transform()
{
}

glm::mat4 Transform::getModel() const
{
  glm::mat4 posMatrix = translate(m_pos);
  glm::mat4 scaleMatrix = scale(m_scale);
  glm::mat4 rotMatrix = glm::mat4_cast(m_rot);
  // glm::mat4 parentMatrix;

  // if(m_parent)
  //   parentMatrix = m_parent->getModel();

  return m_parentMatrix * posMatrix * rotMatrix * scaleMatrix;

}

glm::mat4 Transform::getMVP(const Camera* camera)
{
  //DEBUG("Transform::getMVP");
  ASSERT(camera != nullptr, "Camera == nullptr");

  glm::mat4 VP = camera->getViewProjection();
  glm::mat4 M = getModel();

  return VP * M;
}

glm::mat4 Transform::getMVP(const Camera* camera) const
{
  ASSERT(camera != nullptr, "Camera == nullptr");

  glm::mat4 VP = camera->getViewProjection();
  glm::mat4 M = getModel();

  return VP * M;

}

void Transform::rotate(const float& angle, const glm::vec3& axis)
{
  rotate(glm::angleAxis(angle, axis));
}

void Transform::rotate(glm::quat rotation)
{
  m_rot = glm::normalize(rotation * m_rot);
}

glm::vec3 Transform::get_right()
{
  return Transform::rotate(glm::vec3(1,0,0), m_rot);
}

glm::vec3 Transform::get_left()
{
  return Transform::rotate(glm::vec3(-1,0,0), m_rot);
}

glm::vec3 Transform::get_up()
{
  return Transform::rotate(glm::vec3(0,1,0), m_rot);
}

glm::vec3 Transform::get_down()
{
  return Transform::rotate(glm::vec3(0,-1,0), m_rot);
}

glm::vec3 Transform::get_forward()
{
  return Transform::rotate(glm::vec3(0,0,1), m_rot);
}

glm::vec3 Transform::get_backward()
{
  return Transform::rotate(glm::vec3(0,0,-1), m_rot);
}

glm::vec3 Transform::get_transformed_pos()
{
  return transform(m_parentMatrix, m_pos);
}

glm::quat Transform::get_transformed_rot() 
{
  glm::quat parentRot = glm::quat(0, 0, 0, 1);

  if(m_parent != nullptr)
    parentRot = m_parent->get_transformed_rot();

  return parentRot * get_rot();
}

// glm::vec3& Transform::get_transformed_scale()
// {
 
// }

void Transform::lookAt(glm::vec3 point, glm::vec3 up)
{
  m_rot = get_lookAt_rot(point, up);
}

glm::quat Transform::get_lookAt_rot(glm::vec3 point, glm::vec3 up)
{
  return glm::quat(initRotation(glm::mat4(), glm::normalize(point - m_pos), up));
}

void Transform::set_rot(const glm::quat& rot)
{
  m_rot = rot; 
}  

bool Transform::hasChanged() const
{
  if(m_parent && m_parent->hasChanged())
    return true;

  if(m_pos != m_oldPos || 
     m_rot != m_oldRot || 
     m_scale != m_oldScale)
    return true;

  return false;
}

void Transform::update()
{
  if(hasChanged())
    {
      m_oldPos = m_pos;
      m_oldRot = m_rot;
      m_oldScale = m_scale;

      if(m_parent)
	m_parentMatrix = m_parent->getModel();
    }
}

glm::vec3 Transform::rotate(glm::vec3 v, glm::quat q)
{
  glm::quat w = mul(q, v) * glm::conjugate(q);
  return glm::vec3(w.x, w.y, w.z);
}

glm::quat Transform::mul(glm::quat q, glm::vec3 v)
{
  float w = -q.x * v.x - q.y * v.y - q.z * v.z;
  float x =  q.w * v.x + q.y * v.z - q.z * v.y;
  float y =  q.w * v.y + q.z * v.x - q.x * v.z;
  float z =  q.w * v.z + q.x * v.y - q.y * v.x;

  return glm::quat(w, x, y, z);
}

glm::mat4 Transform::translate(const glm::vec3& v) const
{
  glm::mat4 m;

  for(unsigned int i = 0; i < 4; i++)
    for(unsigned int j = 0; j < 4; j++)
      if(i == 3 && j != 3)
	m[i][j] = v[j];
		
  return m;
}

	
glm::mat4 Transform::scale(const glm::vec3& v) const
{
  glm::mat4 m;
  for(unsigned int i = 0; i < 3; i++)
    for(unsigned int j = 0; j < 3; j++)
      if(i == j && i != 3)
	m[i][j] = v[i];
  
  return m;
}

glm::vec3 transform(glm::mat4 m, glm::vec3 r)
{
  return glm::vec3(m[0][0] * r.x + m[0][1] * r.y + m[0][2] * r.z + m[0][3],
		   m[1][0] * r.x + m[1][1] * r.y + m[1][2] * r.z + m[1][3],
		   m[2][0] * r.x + m[2][1] * r.y + m[2][2] * r.z + m[2][3]);
}


glm::mat4 initRotation(glm::mat4 m, glm::vec3 forward, glm::vec3 up)
{
  glm::vec3 f = glm::normalize(forward);		
  glm::vec3 u = glm::normalize(up);

  glm::vec3 r = cross(u, f);
		
  //glm::vec3 u = cross(f, r);

  return initRotation(m, f, u, r);
}

glm::mat4 initRotation(glm::mat4 m, glm::vec3 forward, glm::vec3 up, glm::vec3 right)
{
  glm::vec3 f = forward;
  glm::vec3 r = glm::normalize(right);
  glm::vec3 u = up;

  m[0][0] = r.x;  m[0][1] = r.y;  m[0][2] = r.z;  m[0][3] = 0;
  m[1][0] = u.x;  m[1][1] = u.y;  m[1][2] = u.z;  m[1][3] = 0;
  m[2][0] = f.x;  m[2][1] = f.y;  m[2][2] = f.z;  m[2][3] = 0;
  m[3][0] = 0;	  m[3][1] = 0;	  m[3][2] = 0;	  m[3][3] = 1;

  return m;
}
