#include "spawner.hpp"
#include "meshRenderer.hpp"
#include "physicsComponent.hpp"
#include "boundingSphere.hpp"
#include "ostream_helper.hpp"

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
		    spawn(t->getPos(), t->getForward()*25.0f);
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
    GameObject* object = new GameObject();
    object->getTransform()->setPos(pos);
    object
	->addComponent(new MeshRenderer(new Mesh("sphere2.obj"), 
					new Material(new Texture("bricks3.jpg"), 
						     glm::vec3(1,1,1), 2 , 1, 
						     new Texture("bricks3_normal.jpg"))))
	->addComponent(new PhysicsComponent(vel, 1.0f, new BoundingSphere(glm::vec3(pos), 1)));

    m_game->getRootObject()->addChild(object);
}
