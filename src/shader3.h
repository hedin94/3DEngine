#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camera.h"
#include "texture.h"

class Shader
{
public:
  Shader(const std::string& filename);
  virtual ~Shader();
 
  void bind();
  void update(const Transform* transform, const Camera* camera);

private:
  static const unsigned int NUM_SHADERS = 2;
  
enum
  {
    TRANSFORM_U,
    MVP_U,
    AMBIENT_LIGHT_U,
    LIGHT_DIRECTION_U,
    DIFFUSE_U,
    NORMAL_MAP_U,

    NUM_UNIFORMS
  };

  GLuint m_program;
  GLuint m_shaders[NUM_SHADERS];
  GLuint m_uniforms[NUM_UNIFORMS];

};

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint createShader(const std::string& text, GLenum shaderType);

#endif // SHADER_H
