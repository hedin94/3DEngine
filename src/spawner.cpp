#include "spawner.hpp"
#include "meshRenderer.hpp"
#include "physicsComponent.hpp"
#include "boundingSphere.hpp"
#include "ostream_helper.hpp"

#include <iostream>

Spawner::Spawner(Uint8 spawnKey) 
    : m_spawnKey(spawnKey) {}

Spawner::~Spawner() {}


void Spawner::input(float delta)
{
    if(!m_spawning) {
	if(Input::get_downKey(m_spawnKey)) {
	    m_spawning = true;
	    Transform * t = getTransform();
	    spawn(t->getPos(), t->getForward()*25.0f);
	}
    } else {
	if(Input::get_upKey(m_spawnKey)) {
	    m_spawning = false;
	}
    }
}


void Spawner::spawn(glm::vec3 pos, glm::vec3 vel)
{
    std::cout << "Spawn sphere at " << pos << std::endl;
    GameObject* object = new GameObject();
    object->getTransform()->setPos(pos);


    Mesh* mesh = new Mesh("sphere.obj");
    float scale = 1/mesh->getBoundingSphere()->getRadius();
    object->getTransform()->setScale({scale, scale, scale});
    object
	->addComponent(new MeshRenderer(mesh, 
					new Material(new Texture("default.jpg"), 
						     glm::vec3(0,1,0), 2 , 1/*,
						     new Texture("bricks3_normal.jpg")*/)))
	->addComponent(new PhysicsComponent(vel, 10.0f, mesh->getBoundingSphere()));

    m_parent->getRoot()->addChild(object);
}
