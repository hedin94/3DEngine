#ifndef COLLIDER_H
#define COLLIDER_H

#include "intersectData.h"

class Collider
{
public:
  Collider();
  virtual ~Collider() = default;

  virtual IntersectData intersect(Collider* other) const = 0;
  virtual void translate(const glm::vec3& translation) = 0;

private:
};

#endif // COLLIDER_H
