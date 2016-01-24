#ifndef CORE_ENGINE_H
#define CORE_ENGINE_H

#include "renderingEngine.h"
#include "game.h"
#include "gameObject.h"
#include "window.h"
#include "input.h"

class RenderingEngine;
class PhysicsEngine;
class GameObject;
class Game;

class CoreEngine
{
public:
  CoreEngine(int width, int height, int framerate, Game* game, std::string title);
  ~CoreEngine();

  void start();
  void stop();

  RenderingEngine* getRenderingEngine() { return m_renderingEngine; }
  PhysicsEngine*   getPhysicsEngine()   { return m_physicsEngine; }

private:
  void createWindow(std::string name);
  void run();

  bool    m_running;
  Game*   m_game;
  Window* m_window;
  Input*  m_input;

  RenderingEngine* m_renderingEngine;
  PhysicsEngine* m_physicsEngine;

  int m_width;
  int m_height;
  int m_ticks_per_frame;
};

#endif // CORE_ENGINE_H
