#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "shader.h"
//#include "lighting.h"
#include "material.h"
#include "camera.h"

class BaseLight;
class DirectionalLight;
class PointLight;
class SpotLight;

class PhongShader : public Shader
{
public:
  static PhongShader* getInstance()
  {
    static PhongShader instance;
    return &instance;
  }

  virtual void update(Transform* transform, Camera* camera, Material* material);

  static glm::vec3& getAmbientLight();
  static DirectionalLight& getDirectionalLight();

  static void setAmbientLight(const glm::vec3& ambientLight);
  static void setDirectionalLight(const DirectionalLight& directionalLight);
  static void setPointLights(PointLight* pointLights, int arraySize);
  static void setSpotLights(SpotLight* spotLights, int arraySize);

private:
  static const int MAX_POINT_LIGHTS = 4;
  static const int MAX_SPOT_LIGHTS = 4;

  static glm::vec3 m_ambientLight;
  static DirectionalLight m_directionalLight;
  static PointLight* m_pointLights;
  static SpotLight* m_spotLights;
  static int m_numPointLights;
  static int m_numSpotLights;

  PhongShader();
  ~PhongShader();
};

#endif // PHONG_SHADER_H
