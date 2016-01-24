#ifndef FORWARD_SPOT_H
#define FORWARD_SPOT_H

#include "shader.h"
#include "lighting.h"
#include <glm/glm.hpp>

class Camera;

class ForwardSpot : public Shader
{
public:
  static ForwardSpot* getInstance()
  {
    static ForwardSpot instance;
    return &instance;
  }

  virtual void update(Transform* transform, RenderingEngine* engine, Material* material);

  static void setSpotLight(const SpotLight& spotLight);

private:
  static SpotLight m_spotLight;

   ForwardSpot();
  ~ForwardSpot();
};

#endif // FORWARD_SPOT_H
