#ifndef BOUNDING_BOX_H
#define BOUDNING_BOX_H

#include <glm/glm.hpp>
#include "intersectData.hpp"
#include "collider.hpp"

class BoundingBox : public Collider
{
public:
  BoundingBox() = default;

  BoundingBox(const glm::vec3& min, const glm::vec3& max)
    : m_min(min), m_max(max) {}

  ~BoundingBox() = default;

  glm::vec3 getMax() const { return m_max; }
  glm::vec3 getMin() const { return m_min; }

  void setMax(const glm::vec3& max) { m_max = max; }
  void setMin(const glm::vec3& min) { m_min = min; }

  virtual IntersectData intersect(Collider* other) const override;

  virtual void translate(const glm::vec3& translation) override;

  void test() const;

private:
  glm::vec3 m_max;
  glm::vec3 m_min;
};

#endif // BOUNDING_BOX_H
