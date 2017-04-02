#include "material.h"
#include <iterator>

Material::Material(Texture* diffuse, glm::vec3 color, float specularIntensity, float specularPower,
		   Texture* normalMap, Texture* dispMap,
		   float dispMapScale, float dispMapOffset)
{
  m_color = color;
  addTexture("diffuse", diffuse);
  addFloat("specularIntensity", specularIntensity);
  addFloat("specularPower", specularPower);
  addTexture("normalMap", normalMap);
  addTexture("dispMap", dispMap);

  float bias = dispMapScale/2.0f;
  addFloat("dispMapScale", dispMapScale);
  addFloat("dispMapBias", -bias + bias*dispMapOffset);
}

Material::~Material()
{
  for(auto it : m_textureMap)
      delete it.second;

  m_textureMap.clear();
}

float Material::getFloat(const std::string& name) const
{
  std::map<std::string, float>::const_iterator it = m_floatMap.find(name);
  if(it != m_floatMap.end())
    return it->second;
			
  return 0;
}

Texture* Material::getTexture(const std::string& name) const
{
  std::map<std::string, Texture*>::const_iterator it = m_textureMap.find(name);
  if(it != m_textureMap.end())
    return it->second;
			
  return nullptr;
}
