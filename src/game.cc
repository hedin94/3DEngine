#include "game.h"
#include "debug.h"

Game::
Game()
{
  m_root = nullptr;
}

Game::
~Game()
{
}

void 
Game::
input(float delta)
{
  getRootObject()->inputAll(delta);
}

void 
Game::
update(float delta)
{
  getRootObject()->updateAll(delta);
}

void 
Game::
render(RenderingEngine* renderingEngine)
{
  // DEBUG("Game::render");
  renderingEngine->render(getRootObject());
}

GameObject* 
Game::
getRootObject()
{
  if(m_root == nullptr)
    m_root = new GameObject();

  return m_root;
}

void 
Game::
setEngine(CoreEngine* engine)
{
  getRootObject()->setEngine(engine); 
}


void
Game::
addToScene(GameObject* child)
{
  DEBUG("Game::addToScene");
  getRootObject()->addChild(child); 
}
