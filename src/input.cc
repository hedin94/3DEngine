#include "input.h"

bool Input::m_quit = false;

std::unordered_set<Uint8> Input::m_downKeys;
std::unordered_set<Uint8> Input::m_upKeys;

std::unordered_set<Uint8> Input::m_downMouseButtons;
std::unordered_set<Uint8> Input::m_upMouseButtons;
 
int Input::m_mouseX = 0;
int Input::m_mouseY = 0;

Input::Input()
{
}

Input::~Input()
{
}

void Input::readInput()
{
  SDL_Event e;

  m_quit = false;

  //m_downKeys.clear();
  //m_upKeys.clear();
  m_downMouseButtons.clear();
  m_upMouseButtons.clear();

  while(SDL_PollEvent(&e))
    {
      switch(e.type)
	{
	case SDL_QUIT:
	  m_quit = true;
	  break;
	case SDL_KEYDOWN:
	  // if(!e.key.repeat)
	  //   {
	  m_downKeys.insert(e.key.keysym.sym);
	  // m_upKeys.erase(e.key.keysym.sym);
	  //}
	  break;
	case SDL_KEYUP:
	  //if(!e.key.repeat)
	  //{
	  //m_upKeys.insert(e.key.keysym.sym);
	  m_downKeys.erase(e.key.keysym.sym);
	  //}
	  break;
	case SDL_MOUSEMOTION:
	  SDL_GetMouseState(&m_mouseX, &m_mouseY);
	  break;
	case SDL_MOUSEBUTTONDOWN:
	  m_downMouseButtons.insert(e.button.button);
	  m_upMouseButtons.erase(e.button.button);
	  break;
	case SDL_MOUSEBUTTONUP:
	  m_upMouseButtons.insert(e.button.button);
	  m_downMouseButtons.erase(e.button.button);
	  break;
	}
    }
}
