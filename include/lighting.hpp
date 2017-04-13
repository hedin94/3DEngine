#ifndef LIGHTING_H
#define LIGHTING_H

#include "gameComponent.hpp"
#include <glm/glm.hpp>

class GameComponent;
class CoreEngine;
class RenderingEngine;
class Shader;

class BaseLight : public GameComponent
{
public:
  BaseLight(/*const std::string& shaderName,*/ glm::vec3 color = glm::vec3(0,0,0), float intensity = 0);

  virtual void input(float delta) {}
  virtual void update(float delta) {}
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) {}

  virtual void addToEngine(CoreEngine* engine);

  virtual Shader* getShader() const { return m_shader; }

  glm::vec3 color;
  float intensity;

protected:
  Shader* m_shader = nullptr;
};

class DirectionalLight : public BaseLight
{
public:
  DirectionalLight(glm::vec3 color = glm::vec3(0,0,0), float intensity = 0);

  //virtual Shader* getShader() const override;

  virtual void update(float delta) override;
  virtual void addToEngine(CoreEngine* engine) override;
  virtual void setParent(GameObject* object) override;

  glm::vec3 direction;

};

struct Attenuation
{
  float constant;
  float linear;
  float exponent;

  Attenuation(float constant = 0, float linear = 0, float exponent = 1);
};

class PointLight : public BaseLight
{
public:
  PointLight(glm::vec3 color = glm::vec3(0,0,0), float intensity = 0, Attenuation atten = Attenuation());//, const std::string& shaderName = "forward-point");

  //virtual Shader* getShader() const override;

  virtual void update(float delta) override;
  virtual void addToEngine(CoreEngine* engine) override;
  virtual void setParent(GameObject* object) override;

  glm::vec3 position;
  Attenuation atten;
  float range;
};

class SpotLight : public PointLight
{

public:
  SpotLight(glm::vec3 color = glm::vec3(0,0,0), float intensity = 0, Attenuation atten = Attenuation(), float cutoff = 0);

  //virtual Shader* getShader() const override;

  virtual void update(float delta) override;
  virtual void addToEngine(CoreEngine* engine) override;
  virtual void setParent(GameObject* object) override;

  glm::vec3 direction;
  float cutoff;
};

#endif
