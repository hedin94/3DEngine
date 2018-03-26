#include "lighting.hpp"
#include "debug.hpp"
#include "shader.hpp"
#include "util.hpp"

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
  direction = getTransform()->getForward();
}

void DirectionalLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}


Attenuation::Attenuation(float constant_, float linear_, float quadratic_)
  : constant(constant_), linear(linear_), quadratic(quadratic_) {}

static const int COLOR_DEPTH = 256;

PointLight::PointLight(glm::vec3 color, float intensity, Attenuation atten_)
  : BaseLight(color, intensity), position(glm::vec3(0,0,0)), atten(atten_)
{
  float e = 0.001;
  float a = atten.quadratic;
  float b = atten.linear;
  float c = atten.constant - COLOR_DEPTH * intensity * std::max(color.x, std::max(color.y, color.z));
  range = (-b + std::sqrt(b*b - (4*a*c)))/(2*a);
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
  position = getTransform()->getPos();
}

void PointLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}


SpotLight::SpotLight(glm::vec3 color, float intensity, Attenuation atten, float viewAngle)
    : PointLight(color, intensity, atten), cutoff(std::cos(toRad(viewAngle)))
{
    std::cout << "SpotLight:\n"
	      << "cutoff: " << cutoff << std::endl;
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
  position = getTransform()->getPos();
  direction = getTransform()->getForward();
}

void SpotLight::setParent(GameObject* parent)
{
  GameComponent::setParent(parent);
}
