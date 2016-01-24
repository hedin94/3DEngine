#include "coreEngine.h"
#include "physicsEngine.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "debug.h"

CoreEngine::CoreEngine(int width, int height, int framerate, Game* game, std::string title)
{
  m_running = false;
  m_game = game;
  m_width = width;
  m_height = height;
  createWindow(title);
  m_ticks_per_frame = 1000/framerate;
  m_renderingEngine = new RenderingEngine();
  m_renderingEngine->setVec3("ambientLight", glm::vec3(0.1f, 0.1f, 0.1f));
  m_physicsEngine = new PhysicsEngine();
  m_game->setEngine(this);
  m_game->init();
  m_input = Input::getInstance();
}

CoreEngine::~CoreEngine()
{
  delete m_renderingEngine;
}

void CoreEngine::start()
{
  DEBUG("Starting core engine");
  if(!m_running)
    run();
}

void CoreEngine::stop()
{
  if(m_running)
    m_running = false;
}

void CoreEngine::run()
{
  m_running = true;

  Uint32 frames = 0;
  Uint32 frameCounter = 0;

  Uint32 lastTime = SDL_GetTicks();
  Uint32 unprocessedTime = 0;

  while(!m_window->isCloseRequested())
    {
      bool render = false;

      Uint32 ticks_at_loop_start = SDL_GetTicks();
      Uint32 passedTime = ticks_at_loop_start - lastTime;
      lastTime = ticks_at_loop_start;

      unprocessedTime += passedTime;
      frameCounter += passedTime;

      while(unprocessedTime > m_ticks_per_frame)
      	{
	  render = true;
	  unprocessedTime -= m_ticks_per_frame;

	  m_input->readInput();
	  m_window->handleInput(m_input);
	  if(m_window->isCloseRequested()) // To be able to close window 
	    break;                         // when nothing is rendered
	  m_physicsEngine->simulate(m_ticks_per_frame);
	  m_physicsEngine->handleCollision(m_ticks_per_frame);
	  m_game->input(m_ticks_per_frame);
	  m_game->update(m_ticks_per_frame);
	}

      if(frameCounter >= 1000)
	{
	  std::string fps("fps: " + std::to_string(frames));
	  std::cout << std::setfill('\b') << std::setw(fps.length() * 2)
		    << fps;

	  frames = 0;
	  frameCounter = 0;
	}

      if(render)
	{
	  frames++;
	  m_window->clear(0.1f, 0.5f, 0.5f, 1.0f);
	  m_game->render(m_renderingEngine);
	  m_window->update();
	}
    }
  stop();
}

void CoreEngine::createWindow(std::string name)
{
  m_window = Window::getInstance(m_width, m_height, name);
}
