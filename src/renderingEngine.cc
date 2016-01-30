#include "renderingEngine.h"
#include "forwardAmbient.h"
#include "forwardDirectional.h"
#include "forwardPoint.h"
#include "forwardSpot.h"
#include "camera.h"
#include "shader.h"
#include <iostream>
#include "debug.h"

RenderingEngine::RenderingEngine()
{
  m_samplerMap.emplace("diffuse", 0);
  m_samplerMap.emplace("normalMap", 1);
  m_samplerMap.emplace("dispMap", 2);

  m_forwardAmbient = new Shader("forward-ambient");
  setVec3("ambientLight", glm::vec3(0.3f, 0.3f, 0.3f));
}

RenderingEngine::~RenderingEngine()
{
}

void RenderingEngine::render(GameObject* object)
{
  object->renderAll(m_forwardAmbient, this);

  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);
  
  glDepthMask(false);
  glDepthFunc(GL_EQUAL);

  renderLight(object);

  glDepthFunc(GL_LESS);
  glDepthMask(true);
  glDisable(GL_BLEND);
}

int RenderingEngine::getSamplerSlot(std::string name)
{
  if(m_samplerMap.find(name) == m_samplerMap.end())
    {
      std::cout << "Sampler " << name << " not found in sampler map" << std::endl;
      return -1;
    }
  else
    return m_samplerMap.at(name);

}

void RenderingEngine::setCamera(Camera* camera)
{
  m_camera = camera;
}

void RenderingEngine::addLight(BaseLight* light)
{
  m_lights.push_back(light);
}

void RenderingEngine::addVec3(const std::string& name, const glm::vec3& value)
{
  m_vec3Map.emplace(name, value);
}

glm::vec3 RenderingEngine::getVec3(const std::string& name) const
{
  //DEBUG(std::string("RenderingEngine::getVec3 - " + name));
  return m_vec3Map.at(name);
}

void RenderingEngine::setVec3(const std::string& name, const glm::vec3& value)
{
  if(m_vec3Map.find(name) == m_vec3Map.end())
    m_vec3Map.emplace(name, value);
  else
    m_vec3Map.at(name) = value;
}

bool RenderingEngine::vec3Exists(const std::string& name) const
{
  return m_vec3Map.find(name) != m_vec3Map.end();
}

Camera* RenderingEngine::getCamera()
{
  return m_camera;
}

BaseLight* RenderingEngine::getActiveLight()
{
  return m_activeLight;
}

void RenderingEngine::setShader(Shader* shader)
{
  m_forwardAmbient = shader;
}

Shader* RenderingEngine::getShader()
{
  return m_forwardAmbient;
}

void RenderingEngine::renderLight(GameObject* object)
{
  //DEBUG("RenderingEngine::renderLight");
  for(auto light : m_lights)
    {
      m_activeLight = light;
      object->renderAll(light->getShader(), this);
    }
}
