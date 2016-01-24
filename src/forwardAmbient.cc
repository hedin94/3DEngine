#include "forwardAmbient.h"
#include "debug.h"

glm::vec3 ForwardAmbient::m_ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);

ForwardAmbient::ForwardAmbient()
  : Shader("forward-ambient")
{
  // addVertexShaderFromFile("forward-ambient.vs");
  // addFragmentShaderFromFile("forward-ambient.fs");

  // addAttributesFromFile("forward-ambient.vs");

  // compileShader();

  // addUniformsFromFile("forward-ambient.vs");
  // addUniformsFromFile("forward-ambient.fs");
}

ForwardAmbient::
~ForwardAmbient()
{
}

void
ForwardAmbient::
update(Transform* transform, RenderingEngine* engine, Material* material)
{
  ASSERT(transform != nullptr, "ForwardAmbient::update");
  ASSERT(engine != nullptr, "ForwardAmbient::update");

  Shader::update(transform, engine, material);

  // material->getTexture("diffuse")->bind(0);

  //DEBUG("ForwardAmbient::update");
  //setUniform("MVP", transform->getMVP(camera));

  // setUniform("diffuse", 0);
  setUniform("ambientLight", m_ambientLight);
}  

glm::vec3&
ForwardAmbient::
getAmbientLight()
{
  return m_ambientLight;
}

void
ForwardAmbient::
setAmbientLight(const glm::vec3& ambientLight)
{
  m_ambientLight = ambientLight;
}
