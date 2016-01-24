#include "shader.h"
#include "texture.h"

#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

Shader::Shader(const std::string& filename)
{
  m_program = glCreateProgram();
  m_shaders[0] = createShader(LoadShader(filename + ".vs"), GL_VERTEX_SHADER);
  m_shaders[1] = createShader(LoadShader(filename + ".fs"), GL_FRAGMENT_SHADER);

  for(unsigned i = 0; i < NUM_SHADERS; i++)
    glAttachShader(m_program, m_shaders[i]);

  glBindAttribLocation(m_program, 0, "position");
  glBindAttribLocation(m_program, 1, "texCoord");
  glBindAttribLocation(m_program, 2, "normal");
  glBindAttribLocation(m_program, 3, "tangent");

  glLinkProgram(m_program);
  CheckShaderError(m_program, GL_LINK_STATUS, true, "ERROR: Program linking failed");

  glValidateProgram(m_program);
  CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "ERROR: Program validation failed");

  m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
  m_uniforms[MVP_U] = glGetUniformLocation(m_program, "MVP");
  m_uniforms[AMBIENT_LIGHT_U] = glGetUniformLocation(m_program, "ambientLight");
  m_uniforms[LIGHT_DIRECTION_U] = glGetUniformLocation(m_program, "lightDirection");
  m_uniforms[DIFFUSE_U] =  glGetUniformLocation(m_program, "diffuse");
  m_uniforms[NORMAL_MAP_U] = glGetUniformLocation(m_program, "normalMap");
}
Shader::~Shader()
{
  for(unsigned i = 0; i < NUM_SHADERS; i++)
    {
      glDetachShader(m_program, m_shaders[i]);
      glDeleteShader(m_shaders[i]);
    }
  glDeleteProgram(m_program);
}

void Shader::bind()
{
  glUseProgram(m_program);
}


void Shader::update(const Transform* transform, const Camera* camera)
{
  glm::mat4 model = transform->getModel();//camera->getViewProjection() *  transform->getModel();
  glm::mat4 MVP = transform->getMVP(camera);

 glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
 glUniformMatrix4fv(m_uniforms[MVP_U], 1, GL_FALSE, &MVP[0][0]);
 glUniform3f(m_uniforms[AMBIENT_LIGHT_U], 0.5f, 0.5f, 0.5f);
 glUniform3f(m_uniforms[LIGHT_DIRECTION_U], 0.0f, -0.7f, 1.0f);
 glUniform1i(m_uniforms[DIFFUSE_U], 0);
 glUniform1i(m_uniforms[NORMAL_MAP_U], 1);
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

static std::string LoadShader(const std::string& fileName)
{
  std::ifstream file;
  file.open(("./res/shaders/" + fileName).c_str());

  std::string output;
  std::string line;

  if(file.is_open())
    {
      while(file.good())
	{
	  getline(file, line);
	  output.append(line + "\n");
	}
    }
  else
    {
      std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

  return output;
}

static GLuint createShader(const std::string& text, GLenum shaderType)
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
  
  return shader;
}
