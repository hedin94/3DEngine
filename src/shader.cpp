#include "shader.hpp"
#include "renderingEngine.hpp"
#include "camera.hpp"
#include "lighting.hpp"
#include "debug.hpp"

#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

Shader::Shader(const std::string& filename)
{
  DEBUG(std::string("Shader constructor for " + filename));
  m_program = glCreateProgram();

  if (m_program == 0) 
    {
      fprintf(stderr, "ERROR: could not create shader program\n");
      exit(1);
    }

  std::string vertexFilename = filename + ".vs";
  std::string fragmentFilename = filename + ".fs";

  addVertexShaderFromFile(vertexFilename);
  addFragmentShaderFromFile(fragmentFilename);

  addAttributesFromFile(vertexFilename);

  compileShader();

  addUniformsFromFile(vertexFilename);
  addUniformsFromFile(fragmentFilename);

  //DEBUG(std::string("Shader constructed for " + filename));
}

Shader::~Shader()
{
  for(std::vector<GLuint>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it) 
    {
      glDetachShader(m_program,*it);
      glDeleteShader(*it);
    }
  glDeleteProgram(m_program);
}

void Shader::bind()
{
  glUseProgram(m_program);

}

void Shader::update(Transform* transform, RenderingEngine* engine, Material* material)
{
  for(auto uniform : m_uniforms)
    {
      std::string name = uniform.first;
      std::string type = uniform.second.type;

      std::string prefix = name.substr(0, 2);
      
      // Transform uniforms (prefix T_)
      if(prefix == "T_")
	{
	  if(name == "T_model")
	    setUniform(name, transform->getModel());
	  else if(name == "T_MVP")
	    setUniform(name, transform->getMVP(engine->getCamera()));
	}
      // RenderingEngine uniforms (prefix R_)
      else if(prefix == "R_")
	{
	  if(name == "R_eyePos")
	    setUniform(name, engine->getCamera()->getTransform()->getPos());
	}      
      // Uniforms without prefix
      else
	{
	  if(type == "sampler2D")
	    {
	      int samplerSlot = engine->getSamplerSlot(name);
	      if(samplerSlot != -1)
		{	      
		  material->getTexture(name)->bind(samplerSlot);
		  setUniform(name, samplerSlot);
		}
	    }
	  else if(type == "float")
	    setUniform(name, material->getFloat(name));
	  else if(type == "DirectionalLight")
	    setUniform(name, dynamic_cast<DirectionalLight*>(engine->getActiveLight()));
	  else if(type == "PointLight")
	    setUniform(name, dynamic_cast<PointLight*>(engine->getActiveLight()));
	  else if(type == "SpotLight")
	    setUniform(name, dynamic_cast<SpotLight*>(engine->getActiveLight()));
	  else if(type == "vec3" && engine->vec3Exists(name))
	    setUniform(name, engine->getVec3(name));
	}

    }
}


void Shader::addUniform(const std::string& uniformName, const std::string& uniformType)
{
  int location = glGetUniformLocation(m_program, uniformName.c_str());  
  assert(location != GL_INVALID_VALUE);
  
  m_uniforms.emplace(uniformName, UniformData(location, uniformType));
}

void Shader::addUniformWithCheck(const std::string& type, const std::string& name, uniform_structs structs)
{
  addUniform(name, type);
  if(structs.find(type) != structs.end())
    for(auto uniform : structs.at(type))
      addUniformWithCheck(uniform.first, name + "." + uniform.second, structs);
}

void Shader::addUniformsFromFile(const std::string& filename)
{
  std::string shaderText = loadShader(filename);

  uniform_structs structs = findUniformStructs(shaderText);

  std::stringstream input(shaderText);
  std::string line;
  while(std::getline(input,line))
    {
      if(line.size() >= 7 && line.substr(0, 7) == "uniform")
	{
	  std::stringstream ss;
	  ss.str(line);
	  std::string type, name;
	  ss >> type >> type >> name;
	  name = name.substr(0, name.size()-1);
	      
	  addUniformWithCheck(type, name, structs);		
	}
    } 
}

void Shader::addAttributesFromFile(const std::string& filename)
{
  std::string shaderText = loadShader(filename);

  std::stringstream input(shaderText);
  std::string line;
  int attribCount{};

  while(std::getline(input,line))
    {
      if(line.size() > 9 && line.substr(0, 9) == "attribute")
	{
	  std::stringstream ss;
	  ss.str(line);
	  std::string type, name;
	  ss >> type >> type >> name;
	  glBindAttribLocation(m_program, attribCount++, name.substr(0, name.size()-1).c_str());
	}
    }   
}

void Shader::addVertexShaderFromFile(const std::string& filename)
{
  addVertexShader(loadShader(filename));
}

void Shader::addGeometryShaderFromFile(const std::string& filename)
{
  addGeometryShader(loadShader(filename));
}

void Shader::addFragmentShaderFromFile(const std::string& filename)
{
  addFragmentShader(loadShader(filename));
}

void Shader::addVertexShader(const std::string& text)
{
  createShader(text, GL_VERTEX_SHADER);
}

void Shader::addGeometryShader(const std::string& text)
{
  createShader(text, GL_GEOMETRY_SHADER);
}

void Shader::addFragmentShader(const std::string& text)
{
  createShader(text, GL_FRAGMENT_SHADER);
}


void Shader::setUniform(const std::string& name, int value)
{
  glUniform1i(m_uniforms.at(name).location, value);
}

void Shader::setUniform(const std::string& name, float value)
{
  glUniform1f(m_uniforms.at(name).location, value);
}

void Shader::setUniform(const std::string& name, const glm::vec3& value)
{
  glUniform3f(m_uniforms.at(name).location, value.x, value.y, value.z);
}

void Shader::setUniform(const std::string& name, const glm::mat4& value)
{
  glUniformMatrix4fv(m_uniforms.at(name).location, 1, GL_FALSE, &(value[0][0]));
}

void Shader::setUniform(const std::string& name, BaseLight* baseLight)
{
  setUniform(name + ".color", baseLight->color);
  setUniform(name + ".intensity", baseLight->intensity);
}

void Shader::setUniform(const std::string& name, DirectionalLight* directionalLight)
{
  setUniform(name + ".base.color", directionalLight->color);
  setUniform(name + ".base.intensity", directionalLight->intensity);
  setUniform(name + ".direction", directionalLight->getTransform()->getForward());
}

void Shader::setUniform(const std::string& name, PointLight* pointLight)
{
  setUniform(name + ".base.color", pointLight->color);
  setUniform(name + ".base.intensity", pointLight->intensity);
  setUniform(name + ".atten.constant", pointLight->atten.constant);
  setUniform(name + ".atten.linear", pointLight->atten.linear);
  setUniform(name + ".atten.exponent", pointLight->atten.exponent);
  setUniform(name + ".position", pointLight->getTransform()->getPos());
  setUniform(name + ".range", pointLight->range);
}

void Shader::setUniform(const std::string& name, SpotLight* spotLight)
{
  setUniform(name + ".pointLight.base.color", spotLight->color);
  setUniform(name + ".pointLight.base.intensity", spotLight->intensity);
  setUniform(name + ".pointLight.atten.constant", spotLight->atten.constant);
  setUniform(name + ".pointLight.atten.linear", spotLight->atten.linear);
  setUniform(name + ".pointLight.atten.exponent", spotLight->atten.exponent);
  setUniform(name + ".pointLight.position", spotLight->getTransform()->getPos());
  setUniform(name + ".pointLight.range", spotLight->range);
  setUniform(name + ".direction", spotLight->getTransform()->getForward());
  setUniform(name + ".cutoff", spotLight->cutoff);
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
  GLint success = 0;
  GLchar error[1024] = { 0 };
  
  if(isProgram)
    glGetProgramiv(shader, flag, &success);
  else
    glGetShaderiv(shader, flag, &success);
  
  if(!success)
    {
      if(isProgram)
	glGetProgramInfoLog(shader, sizeof(error), NULL, error);
      else
	glGetShaderInfoLog(shader, sizeof(error), NULL, error);
      
      fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
    }
}

static std::string loadShader(const std::string& fileName)
{
  std::ifstream file("res/shaders/" + fileName);

  std::string output{};
  std::string line;

  if(file.is_open())
    {
      while(getline(file, line))
	{
	  if(line.size() > 8 && line.substr(0, 8) == "#include")
	    {
	      std::string includeFilename = line.substr(10, line.size()-11);
	      std::string includeText = loadShader(includeFilename);
	      output.append(includeText + "\n");
	    }
	  else
	    output.append(line + "\n");
	}
    }
  else
    {
      std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

  file.close();
  return output;
}

GLuint Shader::createShader(const std::string& text, GLenum shaderType)
{
  GLuint shader = glCreateShader(shaderType);

  if(shader == 0)
    {
      std::cerr << "ERROR: Could not create shader!" << std::endl;
    }
  else
    {      
      GLint shaderSourceStringLength[1];
      const GLchar* shaderSourceStrings[1];
      
      shaderSourceStringLength[0] = text.length();
      shaderSourceStrings[0] = text.c_str();
      
      glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
      glCompileShader(shader);
      
      CheckShaderError(shader, GL_COMPILE_STATUS, false, "ERROR: Shader compilation failed");
    }

  glAttachShader(m_program, shader);
  m_shaders.push_back(shader);  

  return shader;
}

void Shader::compileShader()
{
  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR: Program linking failed");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR: Program validation failed");
}

typename Shader::uniform_structs 
Shader::
findUniformStructs(const std::string& shaderText)
{
  uniform_structs structs;

  std::stringstream input(shaderText);

  std::string line;
  while(std::getline(input, line))
    {
      if(line.substr(0, 6) == "struct")
	{
	  std::stringstream ss;
	  std::string name;
	  ss.str(line);
	  ss >> name >> name;
	  structs.emplace(name, std::vector<std::pair<std::string, std::string> >());
	  while(std::getline(input, line) && line != "};")
	    {
	      if(line == "{")
		continue;
	      ss.clear();
	      ss.str(line);
	      std::string componentType, componentName;
	      ss >> componentType >> componentName;
	      componentName = componentName.substr(0, componentName.size()-1);
	      structs.at(name).push_back(make_pair(componentType, componentName));
	    }

	}
    }

  return structs;
}

