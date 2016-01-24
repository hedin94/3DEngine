#include "physicsEngine.h"
#include "intersectData.h"
#include "boundingSphere.h"
#include <cmath>
#include <iostream>

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}



PhysicsEngine* PhysicsEngine::addObject(PhysicsObject* object)
{
  m_objects.push_back(object);

  return this;
}

void PhysicsEngine::simulate(const float& delta)
{
  for(auto object : m_objects)
    object->update(delta);
}

using namespace std;

void PhysicsEngine::handleCollision(const float& delta)
{
  for(auto i = 0; i < m_objects.size() - 1; i++)
    {
      for(auto j = i+1; j < m_objects.size(); j++)
	{
	  PhysicsObject* object1 = m_objects.at(i);
	  PhysicsObject* object2 = m_objects.at(j);
	  IntersectData data = object1->getCollider()->intersect(object2->getCollider());
	  if(data.intersect)
	    {	     
	      // Update positions

	      glm::vec3 direction1 = object1->getCollider()->intersect(object2->getCollider()).direction;
	      glm::vec3 pos1;
	      glm::vec3 newPos1;
	      if(object1->isMovable())
		{
		  pos1 = object1->getPos();
		  newPos1 = pos1 - delta * object1->getVel(); //glm::dot(direction1, object1->getVel());
		  object1->setPos(newPos1);
		}
	      
	      glm::vec3 direction2 = object2->getCollider()->intersect(object1->getCollider()).direction;
	      glm::vec3 pos2;
	      glm::vec3 newPos2;	      
	      if(object2->isMovable())
		{
		  pos2 = object2->getPos();
		  newPos2 = pos2 - delta * object2->getVel(); //glm::dot(direction2, object2->getVel());
		  object2->setPos(newPos2);
		}

	      // Update velocities
	      float m1 = object1->getMass();
	      float m2 = object2->getMass();

	      direction1 = glm::normalize(direction1);
	      glm::vec3 vel1 = object1->getVel();

	      float x1 = glm::dot(direction1, vel1);

	      glm::vec3 vel1x = direction1 * x1;
	      glm::vec3 vel1y = vel1 - vel1x;

	      direction2 = glm::normalize(direction2);
	      glm::vec3 vel2 = object2->getVel();

	      float x2 = glm::dot(direction2, vel2);

	      glm::vec3 vel2x = direction2 * x2;
	      glm::vec3 vel2y = vel2 - vel2x;

	      glm::vec3 newVel1;
	      glm::vec3 newVel2;
	      if(object1->isMovable())
		{
		  newVel1 = vel1x*(m1-m2)/(m1+m2) + vel2x*(2*m2)/(m1+m2) + vel1y;
		  object1->setVel(newVel1);
		}
	      if(object2->isMovable())
		{
		  newVel2 = vel2x*(m2-m1)/(m1+m2) + vel1x*(2*m1)/(m1+m2) + vel2y;
		  object2->setVel(newVel2);
		}


	      //printMomentum();

	      if(newVel1.z != 0)
		std::cout << "\nZ changed in newVel1!" << std::endl;
	      if(newVel2.z != 0)
		std::cout << "\nZ changed in newVel2!" << std::endl; 
	      
	      // cout << "\nBEFORE:\n"
	      // 	   << "Velocity:\n"
	      // 	   << "(" << vel1.x << ", " << vel1.y << ", " << vel1.z << ")\n"
	      // 	   << "(" << vel2.x << ", " << vel2.y << ", " << vel2.z << ")\n"
	      // 	   << "Position:\n"
	      // 	   << "(" << pos1.x << ", " << pos1.y << ", " << pos1.z << ")\n"
	      // 	   << "(" << pos2.x << ", " << pos2.y << ", " << pos2.z << ")\n";

	      // cout << "AFTER:\n"
		//	   << "Velocity:\n"
		// 	   << "(" << newVel1.x << ", " << newVel1.y << ", " << newVel1.z << ")\n"
		//	   << "(" << newVel2.x << ", " << newVel2.y << ", " << newVel2.z << ")\n";
		   // << "Position:\n"
		   // << "(" << newPos1.x << ", " << newPos1.y << ", " << newPos1.z << ")\n"
		   // << "(" << newPos2.x << ", " << newPos2.y << ", " << newPos2.z << ")\n";


	    }
	}
    }
}


void PhysicsEngine::printVelocity()
{
  glm::vec3 velocity;
  for(auto o : m_objects)
    velocity += o->getVel();

  cout << "Velocity: " 
       << "(" << velocity.x << ", " << velocity.y << ", " << velocity.z << ")" << endl;

}

void PhysicsEngine::printMomentum()
{
  glm::vec3 momentum;
  for(auto o : m_objects)
    momentum += o->getVel() * o->getMass();

  cout << "Momentum: " 
       << "(" << momentum.x << ", " << momentum.y << ", " << momentum.z << ")" << endl;

}
