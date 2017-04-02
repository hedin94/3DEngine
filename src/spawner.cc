#include "spawner.h"
#include "meshRenderer.h"
#include "physicsComponent.h"
#include "boundingSphere.h"

#include "ostream_helper.h"

Spawner::Spawner(Game* game, Uint8 spawnKey) 
  : m_game(game), m_spawnKey(spawnKey) {}

Spawner::~Spawner() {}


void Spawner::input(float delta)
{
  if(!m_spawning) 
    {
      if(Input::get_downKey(m_spawnKey))
	{
	  m_spawning = true;
	  Transform * t = getTransform();
	  spawn(t->get_pos()/*+ (t->get_forward() * 10.0f)*/, t->get_forward()*25.0f);
	}
    }
  else
    {
      if(Input::get_upKey(m_spawnKey))
      	{
      	  m_spawning = false;
      	}
    }
}


void Spawner::spawn(glm::vec3 pos, glm::vec3 vel)
{
  std::cout << "Spawn sphere at " << pos << std::endl;
  GameObject* object = new GameObject(pos);
  object
    ->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
					new Material(new Texture("bricks3.jpg"), 
						     glm::vec3(1,1,1), 2 , 1, 
						     new Texture("bricks3_normal.jpg"))))
    ->addComponent(new PhysicsComponent(vel, 1.0f, new BoundingSphere(glm::vec3(pos), 1)));

  m_game->getRootObject()->addChild(object);
}
