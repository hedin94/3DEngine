#ifndef FORWARD_DIRECTIONAL_H
#define FORWARD_DIRECTIONAL_H

#include "shader.h"
#include "lighting.h"
#include <glm/glm.hpp>

class Camera;

class ForwardDirectional : public Shader
{
public:
  static ForwardDirectional* getInstance()
  {
    static ForwardDirectional instance;
    return &instance;
  }

  virtual void update(Transform* transform, RenderingEngine* engine, Material* material);

  static void setDirectionalLight(const DirectionalLight& directionalLight);

private:
  static DirectionalLight m_directionalLight;

   ForwardDirectional();
  ~ForwardDirectional();
};

#endif // FORWARD_DIRECTIONAL_H
