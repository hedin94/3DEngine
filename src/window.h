#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <string>
#include <glm/glm.hpp>
#include "input.h"

class Window
{
public:
  static Window* getInstance(int width, int height, std::string title)
  {
    static Window instance(width, height, title);
    return &instance;
  }

  static void clear(float r, float g, float b, float a);
  static void update();
  static bool isCloseRequested();
  static void isCloseRequested(bool b) { m_isCloseRequested = b; }
  static bool isPaused();

  static float getAspect();
  static int getWidth();
  static int getHeight();
  static std::string getTitle();

  static SDL_Window* get_window() { return m_window; }
  static bool get_mouseLocked() { return m_mouseLocked; }
  static void set_mouseLocked(bool b) { m_mouseLocked = b; }

  static void handleInput(Input* input);

  static glm::vec2 get_windowCenter() { return glm::vec2((float)m_width/2.0f, (float)m_height/2.0f); }

private:
  Window(int width, int height, std::string title);
  virtual ~Window();

  static int m_width;
  static int m_height;
  static std::string m_title;
  static SDL_Window* m_window;
  static SDL_GLContext m_glContext;
  static bool m_isCloseRequested;
  static bool m_mouseLocked;

  // Temporary
  static bool m_paused;
};
#endif // WINDOW_H
