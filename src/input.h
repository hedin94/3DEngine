#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <unordered_set>
#include <iostream>

class Input
{
public:
  static Input* getInstance()
  {
    static Input instance;
    return &instance;
  }  

  static void readInput();

  static bool get_quit() { return m_quit; }

  static bool get_downKey(const Uint8& key) { return m_downKeys.find(key) != m_downKeys.end(); }
  static bool get_upKey(const Uint8& key) { return m_upKeys.find(key) != m_upKeys.end(); }

  static bool get_downMouseButton(const Uint8& button) { return m_downMouseButtons.find(button) != m_downMouseButtons.end(); }
  static bool get_upMouseButton(const Uint8& button) { return m_upMouseButtons.find(button) != m_upMouseButtons.end(); }

  // bool get_mouseMotion() { return m_mouseMotion; }
  static int get_mouseX() { return m_mouseX; }
  static int get_mouseY() { return m_mouseY; }

  static void set_mouseX(int x) { m_mouseX = x; }
  static void set_mouseY(int y) { m_mouseY = y; }


private:
  Input();
  ~Input();

  static bool m_quit;

  static std::unordered_set<Uint8> m_downKeys;
  static std::unordered_set<Uint8> m_upKeys;

  static std::unordered_set<Uint8> m_downMouseButtons;
  static std::unordered_set<Uint8> m_upMouseButtons;
 
  static int m_mouseX;
  static int m_mouseY;
};
#endif // INPUT_H
