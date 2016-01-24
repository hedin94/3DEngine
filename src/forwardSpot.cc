#include "forwardSpot.h"
#include "debug.h"
#include "camera.h"

SpotLight ForwardSpot::m_spotLight = SpotLight();

ForwardSpot::ForwardSpot()
  : Shader("forward-spot")
{
  // addVertexShaderFromFile("forward-spot.vs");
  // addFragmentShaderFromFile("forward-spot.fs");

  // addAttributesFromFile("forward-spot.vs");

  // compileShader();

  // addUniformsFromFile("forward-spot.vs");
  // addUniformsFromFile("forward-spot.fs");
}

ForwardSpot::
~ForwardSpot()
{
}

void
ForwardSpot::
update(Transform* transform, RenderingEngine* engine, Material* material)
{
  Shader::update(transform, engine, material);

  ASSERT(transform != nullptr, "ForwardSpot::update");
  ASSERT(engine != nullptr, "ForwardSpot::update");

  // material->getTexture("diffuse")->bind(0);
  // material->getTexture("normalMap")->bind(1);

  // setUniform("T_model", transform->getModel());
  // setUniform("T_MVP", transform->getMVP(camera));

  // setUniform("diffuse", 0);
  // setUniform("normalMap", 1);

  // setUniform("specularIntensity", material->getFloat("specularIntensity"));
  // setUniform("specularPower", material->getFloat("specularPower"));
  
  // setUniform("C_eyePos", camera->getTransform()->get_pos());

  // setUniform("spotLight.pointLight.base.color", m_spotLight.color);
  // setUniform("spotLight.pointLight.base.intensity", m_spotLight.intensity);
  // setUniform("spotLight.pointLight.atten.constant", m_spotLight.atten.constant);
  // setUniform("spotLight.pointLight.atten.linear", m_spotLight.atten.linear);
  // setUniform("spotLight.pointLight.atten.exponent", m_spotLight.atten.exponent);
  // setUniform("spotLight.pointLight.position", m_spotLight.position);
  // setUniform("spotLight.pointLight.range", m_spotLight.range);
  // setUniform("spotLight.direction", m_spotLight.direction);
  // setUniform("spotLight.cutoff", m_spotLight.cutoff);
}  

void
ForwardSpot::
setSpotLight(const SpotLight& spotLight)
{
  m_spotLight = spotLight;
}
