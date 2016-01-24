#include "forwardDirectional.h"
#include "debug.h"
#include "camera.h"

DirectionalLight ForwardDirectional::m_directionalLight = DirectionalLight(glm::vec3(0.4f, 0.4f, 0.4f), 1);

ForwardDirectional::ForwardDirectional()
  : Shader("forward-directional")
{
  DEBUG("ForwardDirectional constructor");
  // addVertexShaderFromFile("forward-directional.vs");
  // addFragmentShaderFromFile("forward-directional.fs");

  // addAttributesFromFile("forward-directional.vs");

  // compileShader();

  // addUniformsFromFile("forward-directional.vs");
  // addUniformsFromFile("forward-directional.fs");
}

ForwardDirectional::
~ForwardDirectional()
{
}

void
ForwardDirectional::
update(Transform* transform, RenderingEngine* engine, Material* material)
{
  Shader::update(transform, engine, material);
  //DEBUG("ForwardDirectional::update");
  ASSERT(transform != nullptr, "ForwardDirectional::update");
  ASSERT(engine != nullptr, "ForwardDirectional::update");

  // material->getTexture("diffuse")->bind(0);
  // material->getTexture("normalMap")->bind(1);

  // setUniform("T_model", transform->getModel());
  // setUniform("T_MVP", transform->getMVP(camera));

  // setUniform("diffuse", 0);
  // setUniform("normalMap", 1);

  // setUniform("directionalLight.direction", m_directionalLight.direction);
  // setUniform("directionalLight.base.color", m_directionalLight.color);
  // setUniform("directionalLight.base.intensity", m_directionalLight.intensity);

  // setUniform("specularIntensity", material->getFloat("specularIntensity"));
  // setUniform("specularPower", material->getFloat("specularPower"));
  
  // setUniform("C_eyePos", camera->getTransform()->get_pos());
}  

void
ForwardDirectional::
setDirectionalLight(const DirectionalLight& directionalLight)
{
  m_directionalLight = directionalLight;
}
