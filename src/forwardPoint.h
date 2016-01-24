#ifndef FORWARD_POINT_H
#define FORWARD_POINT_H

#include "shader.h"
#include "lighting.h"
#include <glm/glm.hpp>

class Camera;

class ForwardPoint : public Shader
{
public:
  static ForwardPoint* getInstance()
  {
    static ForwardPoint instance;
    return &instance;
  }

  virtual void update(Transform* transform, RenderingEngine* engine, Material* material);

  static void setPointLight(const PointLight& pointLight);

private:
  static PointLight m_pointLight;

   ForwardPoint();
  ~ForwardPoint();
};

#endif // FORWARD_POINT_H
