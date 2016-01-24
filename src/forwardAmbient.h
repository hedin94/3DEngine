#ifndef FORWARD_AMBIENT_H
#define FORWARD_AMBIENT_H

#include "shader.h"
#include <glm/glm.hpp>

class ForwardAmbient : public Shader
{
public:
  static ForwardAmbient* getInstance()
  {
    static ForwardAmbient instance;
    return &instance;
  }

  virtual void update(Transform* transform, RenderingEngine* engine, Material* material);

  static glm::vec3& getAmbientLight();
  static void       setAmbientLight(const glm::vec3& ambientLight);

private:
  static glm::vec3 m_ambientLight;

   ForwardAmbient();
  ~ForwardAmbient();
};

#endif // FORWARD_AMBIENT_H
