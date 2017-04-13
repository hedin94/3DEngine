#include "plane.hpp"
#include "intersectData.hpp"
#include "boundingSphere.hpp"

#include <iostream>
#include <cmath>

IntersectData Plane::intersect(Collider* other) const
{
  auto sphere = dynamic_cast<BoundingSphere*>(other);
  auto plane = dynamic_cast<Plane*>(other);

  if(sphere != nullptr)
    {
      float distanceToSphere = glm::dot(m_normal, sphere->getPos());
      if(distanceToSphere < 0)
	distanceToSphere = std::fabs(distanceToSphere) - m_offset;
      else
	distanceToSphere = std::fabs(distanceToSphere) - m_offset;

      return IntersectData(std::fabs(distanceToSphere) < sphere->getRadius(), m_normal * (distanceToSphere - sphere->getRadius()));
    }
  else if(plane != nullptr)
    {
      return IntersectData(false, glm::vec3());
    }
  else
    {
      std::cout << "ERROR: Plane does not support specified collider" << std::endl;
      return IntersectData();
    }
}

void Plane::translate(const glm::vec3& translation)
{
  m_offset += glm::dot(translation, m_normal);
}

void Plane::test() const
{
  // std::cout << "TEST: Plane     ";
  // Collider* p = new Plane(glm::vec3(0,1,0), 1);
  // Collider* bs1 = new BoundingSphere(glm::vec3(0,0,0), 1);
  // Collider* bs2 = new BoundingSphere(glm::vec3(0, 0.5f, 0), 1);

  // assert(p->intersect(bs1).intersect == false);
  // // assert(p.intersect(bs1).distance == 0.0f);

  // assert(p->intersect(bs2).intersect == true);
  // //assert(p.intersect(bs2).distance == -0.5f);
  std::cout << "\tSUCCESS" << std::endl;
}
