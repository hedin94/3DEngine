#include "ostream_helper.h"

std::ostream& operator<<(std::ostream& os, glm::vec3& v)
{
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream& operator<<(std::ostream& os, const glm::vec3& v)
{
  return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}
