#ifndef RENDERING_ENGINE_H
#define RENDERING_ENGINE_H

#include "gameObject.h"
//#include "phongShader.h"
//#include "camera.h"
//#include "lighting.h"

#include <vector>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include "texture.h"

class GameObject;
class BaseLight;
class Camera;
class Shader;

class RenderingEngine
{
public:
  RenderingEngine();
  ~RenderingEngine();

  void render(GameObject* object);

  int getSamplerSlot(std::string name);

  void    setCamera(Camera* camera);
  Camera* getCamera();

  void      addVec3(const std::string& name, const glm::vec3& = glm::vec3());
  glm::vec3 getVec3(const std::string& name) const;
  void      setVec3(const std::string& name, const glm::vec3& value);
  bool      vec3Exists(const std::string& name) const;

  void setTexture(const std::string& name, Texture* value);
  Texture* getTexture(const std::string& name);

  void       addLight(BaseLight* light);
  BaseLight* getActiveLight();

  void    setShader(Shader* shader);
  Shader* getShader();

private:
  void renderLight(GameObject* object);

  Shader* m_forwardAmbient{ nullptr };
  Camera* m_camera{ nullptr };

  std::vector<BaseLight*> m_lights;
  BaseLight* m_activeLight{ nullptr };

  std::map<std::string, glm::vec3> m_vec3Map{};
  std::map<std::string, Texture*> m_textureMap{};
  std::map<std::string, int> m_samplerMap{};
};
#endif // RENDERING_ENGINE_H
