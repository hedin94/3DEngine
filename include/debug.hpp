#ifndef ASSERT_H
#define ASSERT_H

#include <stdio.h>

#define ASSERT(condition, message) do { \
if(!(condition)) { printf((message)); } \
 assert ((condition)); } while(false)

#endif // ASSERT_H


#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#ifdef USE_DEBUG
#define DEBUG(message) do { std::cerr << "DEBUG: " << message << '\n'; } while(false)
#else
#define DEBUG(message) do {;} while(false)
#endif // USE_DEBUG

#endif // DEBUG_H
