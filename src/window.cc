#include "window.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>

int Window::m_width;
int Window::m_height;
std::string Window::m_title;
SDL_Window* Window::m_window = nullptr;
SDL_Surface* Window::m_icon = nullptr;
SDL_GLContext Window::m_glContext;
bool Window::m_isCloseRequested = false;
bool Window::m_mouseLocked = false;
bool Window::m_paused = false;

Window::Window(int width, int height, std::string title)
{
  m_width = width;
  m_height = height;
  m_title = title;

  SDL_Init(SDL_INIT_EVERYTHING);
  
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

  SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
  SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );

  m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
  m_glContext = SDL_GL_CreateContext(m_window);

  glewExperimental = GL_TRUE;

  GLenum res = glewInit();
  if(res != GLEW_OK)
    {
      std::cerr << "Could not initialize glew: " << glewGetErrorString(res) << std::endl;
    }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

Window::~Window()
{
  SDL_GL_DeleteContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

bool Window::isCloseRequested()
{
  return m_isCloseRequested;
}

bool Window::isPaused()
{
  return m_paused;
}

float Window::getAspect() 
{
  return (float)m_width / (float)m_height;
}

int Window::getWidth() 
{
  return m_width;
}

int Window::getHeight() 
{
  return m_height;
}

std::string Window::getTitle() 
{
  return m_title;
}

void Window::clear(float r, float g, float b, float a)
{
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
  SDL_GL_SwapWindow(m_window);

  /*SDL_Event e;
    while(SDL_PollEvent(&e))
    {
    switch(e.type)
    {
    case SDL_QUIT:
    m_isCloseRequested = true;
    break;
    }
    }*/
}

void Window::handleInput(Input* input)
{
  //Quit
  if(input->get_quit())
    {
      std::cout << "\nWindow was close requested!" << std::endl;
      m_isCloseRequested = true;
    }

  if(input->get_downKey(SDLK_p))
    m_paused = !m_paused;

}

void Window::setIcon(const std::string& filename) 
{
  if (m_icon == nullptr)
    SDL_FreeSurface(m_icon);

  m_icon = IMG_Load(std::string("./res/icons/" + filename).c_str());
  if(m_icon == NULL)
    std::cerr << "Could not load icon file " << filename << std::endl;
  else
    SDL_SetWindowIcon(m_window, m_icon);
}
