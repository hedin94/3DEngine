#ifndef INTERSECT_DATA_H
#define INTERSECT_DATA_H

#include <glm/glm.hpp>

struct IntersectData
{
  IntersectData(const bool& intersect_, const glm::vec3& direction_)
    : intersect(intersect_), direction(direction_) {}

  IntersectData() = default;
  ~IntersectData() = default;

  bool intersect;
  glm::vec3 direction;
};

#endif // INTERSECT_DATA_H
