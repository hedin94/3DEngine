#include "forwardPoint.h"
#include "debug.h"
#include "camera.h"

PointLight ForwardPoint::m_pointLight = PointLight();

ForwardPoint::ForwardPoint()
  : Shader("forward-point")
{
  // addVertexShaderFromFile("forward-point.vs");
  // addFragmentShaderFromFile("forward-point.fs");

  // addAttributesFromFile("forward-point.vs");

  // compileShader();

  // addUniformsFromFile("forward-point.vs");
  // addUniformsFromFile("forward-pooint.fs");
}

ForwardPoint::
~ForwardPoint()
{
}

void
ForwardPoint::
update(Transform* transform, RenderingEngine* engine, Material* material)
{
  ASSERT(transform != nullptr, "ForwardPoint::update");
  ASSERT(engine != nullptr, "ForwardPoint::update");

  Shader::update(transform, engine, material);

  // material->getTexture("diffuse")->bind(0);
  // material->getTexture("normalMap")->bind(1);

  // setUniform("diffuse", 0);
  // setUniform("normalMap", 1);

  // setUniform("specularIntensity", material->getFloat("specularIntensity"));
  // setUniform("specularPower", material->getFloat("specularPower"));
  
  // setUniform("pointLight.base.color", m_pointLight.color);
  // setUniform("pointLight.base.intensity", m_pointLight.intensity);
  // setUniform("pointLight.atten.constant", m_pointLight.atten.constant);
  // setUniform("pointLight.atten.linear", m_pointLight.atten.linear);
  // setUniform("pointLight.atten.exponent", m_pointLight.atten.exponent);
  // setUniform("pointLight.position", m_pointLight.position);
  // setUniform("pointLight.range", m_pointLight.range);
}  

void
ForwardPoint::
setPointLight(const PointLight& pointLight)
{
  m_pointLight = pointLight;
}
