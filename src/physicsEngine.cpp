#include "physicsEngine.hpp"
#include "intersectData.hpp"
#include "boundingSphere.hpp"
#include "plane.hpp"
#include "ostream_helper.hpp"

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

bool testCollisionSphereSphere(PhysicsObject* object1, PhysicsObject* object2, float& t)
{
  auto bs1 = dynamic_cast<BoundingSphere*>(object1->getCollider());
  auto bs2 = dynamic_cast<BoundingSphere*>(object2->getCollider());

  assert(bs1 != nullptr);
  assert(bs2 != nullptr);

  glm::vec3 s = object1->getPos() - object2->getPos();
  glm::vec3 v = object1->getVel() - object2->getVel();
  float r = bs1->getRadius() + bs2->getRadius();

  float c = glm::dot(s, s) - r*r;
  // cout << "\ns.x: " << s.x;
  // cout << "\n1.x: " << object1->getPos().x; 
  // cout << "\n2.x: " << object2->getPos().x; 

  if(c < 0) // Spheres overlap
    {
      //cout << "collision SphereSphere\n";
      t = 0;
      return true;
    }

  float b = glm::dot(v, s);
  if(b >= 0) // Spheres not moving towards each other
    return false;

  float a = dot(v, v);
  float d = b*b - a*c;
  if(d < 0) // no real root, no collision
    return false;

  //cout << "\na: " << a << "  b: " << b << "  c: " << c << "  d: " << d << endl;
  t = (-b - sqrt(d)) / a;
  //cout << "collision SphereSphere\t" << t << "\n";
  return true;

}

bool testCollisionSpherePlane(PhysicsObject* object1, PhysicsObject* object2, float& t)
{
  auto bs1 = dynamic_cast<BoundingSphere*>(object1->getCollider());
  auto bs2 = dynamic_cast<BoundingSphere*>(object2->getCollider());
  auto plane1 = dynamic_cast<Plane*>(object1->getCollider());
  auto plane2 = dynamic_cast<Plane*>(object2->getCollider());
  
  assert((bs1 != nullptr && plane2 != nullptr) ||
	 (bs2 != nullptr && plane1 != nullptr));
  
  BoundingSphere* bs;
  Plane* p;
  glm::vec3 s;
  glm::vec3 v;

  if(bs1 && plane2)
    {
      bs = bs1;
      p = plane2;
      s = object1->getCollider()->intersect(object2->getCollider()).direction;
      v = object2->getVel() - object1->getVel();
    }
  else 
    {
      bs = bs2;
      p = plane1;
      s = object2->getCollider()->intersect(object1->getCollider()).direction;
      v = object1->getVel() - object2->getVel();
    }

  glm::vec3 normal = p->getNormal();
  glm::vec3 spherePos = bs->getPos();
  float r =  bs->getRadius();
  float distance = (-glm::dot(normal, spherePos) + p->getOffset()) - r;

  float c = distance;
  if(c < 0) // Plane and sphere intersect
    {
      t = 0;
      return true;
    }

  float b = glm::dot(v, s);
  if(b >= 0) // not moving towards each other
    return false;

  float a = dot(v, v); // |v|^2
  float d = b*b - a*c;
  if(d < 0) // no real root, no collision
    return false;
 
  // if(distance < 2)
  //   cout << "\nDistance: " << distance << endl;

  t = (-b - sqrt(d)) / a;
  return true;
}



void PhysicsEngine::handleCollision(const float& delta)
{
  for(int i = 0; i < m_objects.size() - 1; i++)
    {
      for(int j = i + 1; j < m_objects.size(); j++)
	{
	  PhysicsObject* object1 = m_objects.at(i);
	  PhysicsObject* object2 = m_objects.at(j);
	  // IntersectData data = object1->getCollider()->intersect(object2->getCollider());
	  // if(data.intersect)
	  //   {

	  auto bs1 = dynamic_cast<BoundingSphere*>(object1->getCollider());
	  auto bs2 = dynamic_cast<BoundingSphere*>(object2->getCollider());
	  auto plane1 = dynamic_cast<Plane*>(object1->getCollider());
	  auto plane2 = dynamic_cast<Plane*>(object2->getCollider());

	  float t = 0;
	  bool collision = false;

	  if(bs1 && bs2)
	    {
	      collision = testCollisionSphereSphere(object1, object2, t);
	      //cout << boolalpha << "\nt: " << t << "  Collision: " << collision << endl;
	    }

	  else if(bs1 && plane2)
	    {
	      collision = testCollisionSpherePlane(object1, object2, t);
	      // cout << boolalpha << "\n(1,2) t: " << t << "  Collision: " << collision << endl;
	    }

	  else if(bs2 && plane1)
	    {
	      collision = testCollisionSpherePlane(object2, object1, t);
	      //cout << boolalpha << "\n(2,1) t: " << t << "  Collision: " << collision << endl;
	    }

	  if(collision && t >= 0 && t <= delta)
	    {
	      // cout << "\n" << t << " <= " << delta << endl;
	      
	      glm::vec3 pos1 = object1->getPos();
	      glm::vec3 pos2 = object2->getPos();
	      glm::vec3 newPos1 = pos1 + 0.9999f*t*object1->getVel();
	      glm::vec3 newPos2 = pos2 + 0.9999f*t*object2->getVel();

	      //cout << "\nnewPos1: (" << newPos1.x << ", " << newPos1.y << ", " << newPos1.z << ")";
	      //cout << "\nnewPos2: (" << newPos2.x << ", " << newPos2.y << ", " << newPos2.z << ")\n";
	      // cout << "\npos1:\t" << pos1
	      // 	   << "\nNewPos1\t" << newPos1
	      // 	   << "\npos2:\t" << pos2
	      // 	   << "\nnewPos2\t" << newPos2;

	      object1->setPos(newPos1);
	      object2->setPos(newPos2);

	      if(bs1) 
		assert(bs1->getPos() == object1->getPos());
	      if(bs2) 
		assert(bs2->getPos() == object2->getPos());


	      // Update velocity
	      float m1 = object1->getMass();
	      float m2 = object2->getMass();

	      glm::vec3 x = object1->getCollider()->intersect(object2->getCollider()).direction;
	      if(x != glm::vec3())
		x = glm::normalize(x);

	      glm::vec3 vel1 = object1->getVel();
	      float x1 = glm::dot(x, vel1);

	      glm::vec3 vel1x = x * x1;
	      glm::vec3 vel1y = vel1 - vel1x;

	      x = -x;

	      glm::vec3 vel2 = object2->getVel();
	      float x2 = glm::dot(x, vel2);

	      glm::vec3 vel2x = x * x2;
	      glm::vec3 vel2y = vel2 - vel2x;

	      glm::vec3 newVel1 = glm::vec3();
	      glm::vec3 newVel2 = glm::vec3();

	      const float e = 0.99f;
	      if(object1->isMovable())
		{
		  newVel1 = vel1x*(m1-m2)/(m1+m2) + vel2x*(2*m2)/(m1+m2) + vel1y;
		  object1->setVel(newVel1*e);
		  //cout << "\nnewVel1: (" << newVel1.x << ", " << newVel1.y << ", " << newVel1.z << ")";
		}
	      if(object2->isMovable())
		{
		  newVel2 = vel2x*(m2-m1)/(m1+m2) + vel1x*(2*m1)/(m1+m2) + vel2y;
		  object2->setVel(newVel2*e);
		  // cout << "\nnewVel2: (" << newVel2.x << ", " << newVel2.y << ", " << newVel2.z << ")";
		}


	      // cout << "\nnewVel1:\n"
	      //      << "(" << vel1.x << ", " << vel1.y << ", " << vel1.z << ")\n"
	      //      << "(" << newVel1.x << ", " << newVel1.y << ", " << newVel1.z << ")\n";
		  
	      // cout << "\nnewVel2:\n"
	      //      << "(" << vel2.x << ", " << vel2.y << ", " << vel2.z << ")\n"
	      //      << "(" << newVel2.x << ", " << newVel2.y << ", " << newVel2.z << ")\n";
	    }
	

	  // Update positions

	  // glm::vec3 direction1 = object2->getCollider()->intersect(object1->getCollider()).direction;
	  // glm::vec3 pos1;
	  // glm::vec3 newPos1;
	  // if(object1->isMovable())
	  // 	{
	  // 	  pos1 = object1->getPos();
	  // 	  newPos1 = pos1 - (1.0f * delta * object1->getVel()); //glm::dot(direction1, object1->getVel());
	  // 	  object1->setPos(newPos1);
	  // 	}
	      
	  // glm::vec3 direction2 = object1->getCollider()->intersect(object2->getCollider()).direction;
	  // glm::vec3 pos2;
	  // glm::vec3 newPos2;      
	  // if(object2->isMovable())
	  // 	{
	  // 	  pos2 = object2->getPos();
	  // 	  newPos2 = pos2 - (1.0f * delta * object2->getVel()); //glm::dot(direction2, object2->getVel());
	  // 	  object2->setPos(newPos2);
	  // 	}

	      
	  // Update velocities
	  // float m1 = object1->getMass();
	  // float m2 = object2->getMass();

	  // direction1 = glm::normalize(direction1);
	  // glm::vec3 x = glm::normalize(pos1-pos2);
	  // glm::vec3 vel1 = object1->getVel();

	  // float x1 = glm::dot(direction1, vel1);

	  // glm::vec3 vel1x = direction1 * x1;
	  // glm::vec3 vel1y = vel1 - vel1x;

	  // direction2 = glm::normalize(direction2);
	  // glm::vec3 vel2 = object2->getVel();

	  // float x2 = glm::dot(direction2, vel2);

	  // glm::vec3 vel2x = direction2 * x2;
	  // glm::vec3 vel2y = vel2 - vel2x;

	  // glm::vec3 newVel1;
	  // glm::vec3 newVel2;
	  // if(object1->isMovable())
	  // 	{
	  // 	  newVel1 = vel1x*(m1-m2)/(m1+m2) + vel2x*(2*m2)/(m1+m2) + vel1y;
	  // 	  object1->setVel(newVel1);
	  // 	}
	  // if(object2->isMovable())
	  // 	{
	  // 	  newVel2 = vel2x*(m2-m1)/(m1+m2) + vel1x*(2*m1)/(m1+m2) + vel2y;
	  // 	  object2->setVel(newVel2);
	  // 	}

	          



	  //printMomentum();

	  // if(newVel1.z != 0)
	  // 	std::cout << "\nZ changed in newVel1!" << std::endl;
	  // if(newVel2.z != 0)
	  // 	std::cout << "\nZ changed in newVel2!" << std::endl; 
	      
	  // cout << "\nBEFORE:\n"
	  // 	   << "Velocity:\n"
	  // 	   << "(" << vel1.x << ", " << vel1.y << ", " << vel1.z << ")\n"
	  // 	   << "(" << vel2.x << ", " << vel2.y << ", " << vel2.z << ")\n"
	  // 	   << "Position:\n"
	  // 	   << "(" << pos1.x << ", " << pos1.y << ", " << pos1.z << ")\n"
	  // 	   << "(" << pos2.x << ", " << pos2.y << ", " << pos2.z << ")\n";
	      

	  // cout << "\nnewVel1:\n"
	  // 	   << "(" << newVel1.x << ", " << newVel1.y << ", " << newVel1.z << ")\n";
	      
	  // cout << "\nnewVel2:\n"
	  // 	   << "(" << newVel2.x << ", " << newVel2.y << ", " << newVel2.z << ")\n";
	      
	  // cout  << "Position:\n"
	  // 	    << "(" << newPos1.x << ", " << newPos1.y << ", " << newPos1.z << ")\n"
	  // 	    << "(" << newPos2.x << ", " << newPos2.y << ", " << newPos2.z << ")\n";
	      

	  //}
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
       << "(" << momentum.x << ", " << momentum.y << ", " << momentum.z << ")  " << fabs(momentum.x) + fabs(momentum.y) + fabs(momentum.z) << endl;

}
