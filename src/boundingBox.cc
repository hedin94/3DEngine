#include "boundingBox.h"
#include <cmath>
#include <iostream>

bool operator<(const glm::vec3& left, const glm::vec3& right)
{
  return left.x < right.x || left.y < right.y || left.z < right.z;
}

IntersectData BoundingBox::intersect(Collider* other) const
{
  auto bb = dynamic_cast<BoundingBox*>(other);
  if(bb != nullptr)
    {
      glm::vec3 distance1 = bb->getMin() - getMax();
      glm::vec3 distance2 = getMin() - bb->getMax();
      glm::vec3 distance = glm::max(distance1, distance2);
    
      return IntersectData(distance < glm::vec3(), distance);
    }
  else
    {
      std::cout << "ERROR: BoundingBox does not support specified collider" << std::endl;
      return IntersectData();
    }
}

void BoundingBox::translate(const glm::vec3& translation)
{
  m_min += translation;
  m_max += translation;
}

void BoundingBox::test() const
{
  std::cout << "TEST: BoundingBox";
  Collider* bb1 = new BoundingBox(glm::vec3(0,0,0), glm::vec3(1,1,1));
  Collider* bb2 = new BoundingBox(glm::vec3(1,1,1), glm::vec3(2,2,2));
  Collider* bb3 = new BoundingBox(glm::vec3(0.5f, 0, 0), glm::vec3(1.5f, 1, 1));
  
  assert(bb1->intersect(bb2).intersect == false);
  //assert(bb1.intersect(bb2).distance == 0.0f);

  assert(bb1->intersect(bb3).intersect == true);
  //assert(bb1.intersect(bb3).distance == -1.0f);

  assert(bb2->intersect(bb3).intersect == true);
  //assert(bb2.intersect(bb3).distance == -0.5f);
  std::cout << "\tSUCCESS" << std::endl;
}
