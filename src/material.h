#ifndef MATERIAL_H
#define MATERIAL_H

#include "texture.h"
#include <map>
#include <glm/glm.hpp>

class Material
{
public:
  Material() {}
	
  virtual ~Material();
	
  Material(Texture* diffuse, Texture* normalMap = new Texture("default_normal.jpg"), glm::vec3 color = glm::vec3(1,1,1), float specularIntensity = 1.0f, float specularPower = 0);
	
  void addFloat(const std::string& name, float value) { m_floatMap.insert(std::pair<std::string, float>(name, value)); }
  void addTexture(const std::string& name, Texture* value) { m_textureMap.insert(std::pair<std::string, Texture*>(name, value)); }


  float getFloat(const std::string& name) const;	
  Texture* getTexture(const std::string& name) const;

  glm::vec3 getColor() { return m_color; }

protected:
private:
  Material(const Material& other) {}
  void operator=(const Material& other) {}

  std::map<std::string, float> m_floatMap;
  std::map<std::string, Texture*> m_textureMap;

  glm::vec3 m_color;
};

#endif // MATERAL_H
