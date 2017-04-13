#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>
#include "collider.hpp"

struct IntersectData;
class BoundingSphere;

class Plane : public Collider
{
public:
  Plane() = default;
  Plane(const glm::vec3& normal, const float& offset)
    : m_normal(glm::normalize(normal)), m_offset(offset) {}

  ~Plane() = default;

  virtual IntersectData intersect(Collider* other) const override;
  virtual void translate(const glm::vec3& translation) override;

  glm::vec3 getNormal() const { return m_normal; }
  float     getOffset() const { return m_offset; }

  void setNormal(const glm::vec3& normal) { m_normal = glm::normalize(normal); }
  void setOffset(const float& offset)     {  m_offset = offset; }

  void test() const;

private:
  glm::vec3 m_normal;
  float m_offset;
};

#endif // PLANE_H
