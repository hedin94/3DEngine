#include "lighting.hpp"
#include "debug.hpp"
#include "shader.hpp"

#include <glm/gtx/quaternion.hpp>
#include <algorithm>
#include <cmath>

BaseLight::BaseLight(glm::vec3 color, float intensity)
{
  this->color = color;
  this->intensity = intensity;
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

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten_)
  : BaseLight(color, intensity), position(glm::vec3(0,0,0)), atten(atten_)
{
  float a = atten.exponent;
  float b = atten.linear;
  float c = atten.constant - COLOR_DEPTH * intensity * std::max(color.x, std::max(color.y, color.z));
  float e = 0.000001;
  range = (-b + std::sqrt(b*b - (4*a*c)))/(2*a);
  //range = (std::sqrt(-4*a*c*e*e + 4*a*e + b*b*e*e) - b*e) / (2*a*e);
  //range = std::abs((1 - c*e)/(b*e));
  std::cout << "PointLight Range: " << range << std::endl;
  if(m_shader != nullptr)
    delete m_shader;
  m_shader = new Shader("forward-point");
}

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


SpotLight::SpotLight(glm::vec3 color, float intensity, Attenuation atten, float viewAngle)
    : PointLight(color, intensity, atten), cutoff(std::cos(viewAngle))
{
  if(m_shader != nullptr)
    delete m_shader;
  m_shader = new Shader("forward-spot");
}

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
