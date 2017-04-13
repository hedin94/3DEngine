#include "lighting.hpp"
#include "debug.hpp"
#include "shader.hpp"

#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <cmath>

BaseLight::BaseLight(/*const std::string& shaderName,*/ glm::vec3 color, float intensity)
{
  this->color = color;
  this->intensity = intensity;
  //m_shader = new Shader("forward-ambient");
}

void BaseLight::addToEngine(CoreEngine* engine)
{
  engine->getRenderingEngine()->addLight(this);
}

DirectionalLight::DirectionalLight(glm::vec3 color, float intensity)
  : BaseLight(color, intensity)
{
  if(m_shader != nullptr)
    delete m_shader;
  m_shader = new Shader("forward-directional");
}   

// Shader* DirectionalLight::getShader() const
// {
//   return ForwardDirectional::getInstance();
// }


void DirectionalLight::addToEngine(CoreEngine* engine)
{
  engine->getRenderingEngine()->addLight(this);
}

void DirectionalLight::update(float delta)
{
  direction = getTransform()->get_forward();
}

void DirectionalLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}



Attenuation::Attenuation(float constant_, float linear_, float exponent_)
  : constant(constant_), linear(linear_), exponent(exponent_) {}

static const int COLOR_DEPTH = 256;

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten_)//, const std::string& shaderName)
  : BaseLight(color, intensity), position(glm::vec3(0,0,0)), atten(atten_)
{  
  float a = atten.exponent;
  float b = atten.linear;
  float c = atten.constant - COLOR_DEPTH * intensity * std::max(color.x, std::max(color.y, color.z));
  
  range = (-b + std::sqrt(b*b - (4*a*c)))/(2*a);

  if(m_shader != nullptr)
    delete m_shader;
  m_shader = new Shader("forward-point");
}

// Shader* PointLight::getShader() const
// {
//   return ForwardPoint::getInstance();
// }

void PointLight::addToEngine(CoreEngine* engine)
{
  engine->getRenderingEngine()->addLight(this);
}

void PointLight::update(float delta)
{
  position = getTransform()->get_pos();
}

void PointLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}


SpotLight::SpotLight(glm::vec3 color, float intensity, Attenuation atten, float cutoff_)
  : PointLight(color, intensity, atten), cutoff(cutoff_) 
{
  if(m_shader != nullptr)
    delete m_shader;
  m_shader = new Shader("forward-spot");
}

// Shader* SpotLight::getShader() const
// {
//   return ForwardSpot::getInstance();
// }

void SpotLight::addToEngine(CoreEngine* engine)
{
  engine->getRenderingEngine()->addLight(this);
}

void SpotLight::update(float delta)
{
  position = getTransform()->get_pos();
  direction = getTransform()->get_forward(); 
}

void SpotLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}
