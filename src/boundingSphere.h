#ifndef BOUNDING_SPHERE_H
#define BOUDNING_SPHERE_H

#include <glm/glm.hpp>
#include "intersectData.h"
#include "collider.h"

class BoundingSphere : public Collider
{
public:
  BoundingSphere() = default;
  BoundingSphere(const glm::vec3& pos, const float& radius)
    : m_pos(pos), m_radius(radius) {}

  ~BoundingSphere() = default;

  glm::vec3 getPos() const { return m_pos; }
  float getRadius() const { return m_radius; }

  void setPos(const glm::vec3& pos) { m_pos = pos; }
  void setRadius(const float& radius) { m_radius = radius; }

  virtual IntersectData intersect(Collider* other) const override;

  virtual void translate(const glm::vec3& translation) override;

  void test() const;

private:
  glm::vec3 m_pos;
  float m_radius;
};

#endif // BOUNDING_SPHERE_H
