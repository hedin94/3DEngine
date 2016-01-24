#include "phongShader.h"
#include "lighting.h"

glm::vec3 PhongShader::m_ambientLight = glm::vec3(0.1f,0.1f,0.1f);
DirectionalLight PhongShader::m_directionalLight = DirectionalLight(glm::vec3(0.3f, 0.3f, 0.3f), 1, glm::vec3(0,-0.7,1));
PointLight* PhongShader::m_pointLights = NULL;
SpotLight* PhongShader::m_spotLights = NULL;
int PhongShader::m_numPointLights = 0;
int PhongShader::m_numSpotLights = 0;

PhongShader::PhongShader()
{
  addVertexShaderFromFile("phongShader.vs");
  addFragmentShaderFromFile("phongShader.fs");

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");
  glBindAttribLocation(m_program, 3, "tangent");

  compileShader();

  addUniform("transform");
  addUniform("MVP");
  addUniform("baseColor");

  addUniform("diffuse");
  addUniform("normalMap");
		
  addUniform("ambientLight");
  addUniform("specularIntensity");
  addUniform("specularPower");
  addUniform("eyePos");
		
  addUniform("directionalLight.base.color");
  addUniform("directionalLight.base.intensity");
  addUniform("directionalLight.direction");

  for(int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
      std::string pointLightName = "pointLights[" + std::to_string(i) + "]";

      addUniform(pointLightName + ".base.color");
      addUniform(pointLightName + ".base.intensity");
      addUniform(pointLightName + ".atten.constant");
      addUniform(pointLightName + ".atten.linear");
      addUniform(pointLightName + ".atten.exponent");
      addUniform(pointLightName + ".position");
      addUniform(pointLightName + ".range");
    }

  for(int i = 0; i < MAX_SPOT_LIGHTS; i++)
    {
      std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

      addUniform(spotLightName + ".pointLight.base.color");
      addUniform(spotLightName + ".pointLight.base.intensity");
      addUniform(spotLightName + ".pointLight.atten.constant");
      addUniform(spotLightName + ".pointLight.atten.linear");
      addUniform(spotLightName + ".pointLight.atten.exponent");
      addUniform(spotLightName + ".pointLight.position");
      addUniform(spotLightName + ".pointLight.range");
      addUniform(spotLightName + ".direction");
      addUniform(spotLightName + ".cutoff");
    }
}

PhongShader::~PhongShader()
{
}

void PhongShader::update(Transform* transform, Camera* camera, Material* material)
{
  material->getTexture("diffuse")->bind(0);
  material->getTexture("normalMap")->bind(1);

  setUniform("transform", transform->getModel());
  setUniform("MVP", transform->getMVP(camera));
  setUniform("baseColor", material->getColor());

  setUniformi("diffuse", 0);
  setUniformi("normalMap", 1);

  setUniform("ambientLight", m_ambientLight);
  setUniform("directionalLight.direction", m_directionalLight.direction);
  setUniform("directionalLight.base.color", m_directionalLight.color);
  setUniformf("directionalLight.base.intensity", m_directionalLight.intensity);
  
  for(int i = 0; i < m_numPointLights; i++)
    {
      std::string pointLightName = "pointLights[" + std::to_string(i) + "]";
      
      setUniform(pointLightName + ".base.color", m_pointLights[i].color);
      setUniformf(pointLightName + ".base.intensity", m_pointLights[i].intensity);
      setUniformf(pointLightName + ".atten.constant", m_pointLights[i].atten.constant);
      setUniformf(pointLightName + ".atten.linear", m_pointLights[i].atten.linear);
      setUniformf(pointLightName + ".atten.exponent", m_pointLights[i].atten.exponent);
      setUniform(pointLightName + ".position", m_pointLights[i].position);
      setUniformf(pointLightName + ".range", m_pointLights[i].range);
    }


  for(int i = 0; i < m_numSpotLights; i++)
    {
      std::string spotLightName = "spotLights[" + std::to_string(i) + "]";

      setUniform(spotLightName + ".pointLight.base.color", m_spotLights[i].color);
      setUniformf(spotLightName + ".pointLight.base.intensity", m_spotLights[i].intensity);
      setUniformf(spotLightName + ".pointLight.atten.constant", m_spotLights[i].atten.constant);
      setUniformf(spotLightName + ".pointLight.atten.linear", m_spotLights[i].atten.linear);
      setUniformf(spotLightName + ".pointLight.atten.exponent", m_spotLights[i].atten.exponent);
      setUniform(spotLightName + ".pointLight.position", m_spotLights[i].position);
      setUniformf(spotLightName + ".pointLight.range", m_spotLights[i].range);
      setUniform(spotLightName + ".direction", m_spotLights[i].direction);
      setUniformf(spotLightName + ".cutoff", m_spotLights[i].cutoff);
    }

  setUniformf("specularIntensity", material->getFloat("specularIntensity"));
  setUniformf("specularPower", material->getFloat("specularPower"));
  
  setUniform("eyePos", camera->getPos());
}

glm::vec3& PhongShader::getAmbientLight()
{
  return m_ambientLight;
}

DirectionalLight& PhongShader::getDirectionalLight()
{
  return m_directionalLight;
}


void PhongShader::setAmbientLight(const glm::vec3& ambientLight)
{
  m_ambientLight = ambientLight;
}

void PhongShader::setDirectionalLight(const DirectionalLight& directionalLight)
{
  m_directionalLight = directionalLight;
}

void PhongShader::setPointLights(PointLight* pointLights, int arraySize)
{
  if(arraySize > MAX_POINT_LIGHTS)
    {
      std::cout << "You passed in " << arraySize << " point lights, max " << MAX_POINT_LIGHTS << " is allowed!" << std::endl;
    }
  else
    {
      m_pointLights = pointLights;
      m_numPointLights = arraySize;
    }
}

void PhongShader::setSpotLights(SpotLight* spotLights, int arraySize)
{
  if(arraySize > MAX_SPOT_LIGHTS)
    {
      std::cout << "You passed in " << arraySize << " spot lights, max " << MAX_SPOT_LIGHTS << " is allowed!" << std::endl;
    }
  else
    {
      m_spotLights = spotLights;
      m_numSpotLights = arraySize;
    }
}

