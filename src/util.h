#ifndef UTIL_H
#define UTIL_H
#include "constants.h"

constexpr float toRad(float deg) { return deg * constants::PIdiv180; }

#endif
