#ifndef OSTREAM_HELPER_H
#define OSTREAM_HELPER_H

#include <iostream>
#include <glm/glm.hpp>

std::ostream& operator<<(std::ostream& os, glm::vec3& v);
std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

#endif // OSTREAM_HELPER_H
