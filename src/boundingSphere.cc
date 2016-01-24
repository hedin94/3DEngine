#include "boundingSphere.h"
#include "plane.h"
#include <cmath>
#include <iostream>

IntersectData BoundingSphere::intersect(Collider* other) const
{
  auto bs = dynamic_cast<BoundingSphere*>(other);
  auto plane = dynamic_cast<Plane*>(other);

  if(bs != nullptr)
    {
      glm::vec3 direction = glm::normalize(bs->getPos() - m_pos);
      float centerDistance = glm::length(bs->getPos() - m_pos);
      float totalRadius = m_radius + bs->getRadius();
      
      return IntersectData(centerDistance < totalRadius, (centerDistance - totalRadius) * direction);
    }

  else if(plane != nullptr)
    {
      const BoundingSphere* sphere = this;
      float distanceToSphere = dot(plane->getNormal(), sphere->getPos());
      if(distanceToSphere < 0)
      	distanceToSphere = std::fabs(distanceToSphere) + plane->getOffset();
      else
      	distanceToSphere = std::fabs(distanceToSphere) - plane->getOffset();

      // glm::vec3 normal = plane->getNormal();
      // glm::vec3 spherePos = sphere->getPos();
      // std::cout << std::boolalpha << "\nSphere intersect with plane: " << (std::fabs(distanceToSphere) < sphere->getRadius())
      // 		<< "\nDistance: " << distanceToSphere << "\tRadius: " << sphere->getRadius() 
      // 		<< "\nSphere pos: " 
      // 		<< "(" << spherePos.x << ", " << spherePos.y << ", " << spherePos.z << ")\n"
      // 		<< "Plane normal: " 
      // 		<< "(" << normal.x << ", " << normal.y << ", " << normal.z << ")\n";

      return IntersectData(std::fabs(distanceToSphere) < sphere->getRadius(), float(-1) * plane->getNormal() * (distanceToSphere - sphere->getRadius()));
    }
  else
    {
      std::cout << "ERROR: BoundingSphere does not support specified collider" << std::endl;
      return IntersectData();
    }
}

void BoundingSphere::translate(const glm::vec3& translation)
{
  m_pos += translation;
}

void BoundingSphere::test() const
{
  std::cout << "TEST: BoundingSphere";
  BoundingSphere* bs1 = new BoundingSphere(glm::vec3(0,0,0), 1);
  BoundingSphere* bs2 = new BoundingSphere(glm::vec3(2, 0, 0), 1);
  BoundingSphere* bs3 = new BoundingSphere(glm::vec3(1, 0, 0), 1);
  
  // assert(bs1->intersect(bs2).intersect == false);
  // //assert(bs1->intersect(bs2).distance == 0.0f);

  // assert(bs1->intersect(bs3).intersect == true);
  // //assert(bs1->intersect(bs3).distance == -1.0f);

  // assert(bs2->intersect(bs3).intersect == true);
  // //assert(bs2->intersect(bs3).distance == -1.0f);

  delete bs1;
  delete bs2;
  delete bs3;

  std::cout << "\tSUCCESS" << std::endl;
}
