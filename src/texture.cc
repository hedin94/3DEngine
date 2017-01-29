#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
#include <GL/glew.h>

Texture::Texture(const std::string& filename)
{
  int width, height, numComponents;
  unsigned char* imgData = stbi_load(("./res/textures/" + filename).c_str(), &width, &height, &numComponents, 4);

  if(imgData == NULL)
    std::cerr << "ERROR: Could not load texture " << filename << std::endl;

  glGenTextures(1, &m_texture);
  glBindTexture(GL_TEXTURE_2D, m_texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

  stbi_image_free(imgData);
}


Texture::Texture(int width, int height, unsigned char* data, GLenum textureTarget, GLfloat filter, GLint internalFormat, GLenum format, bool clamp)
{
  if(width > 0 && height > 0 && data != 0)
    {
      glGenTextures(1, &m_texture);
      glBindTexture(textureTarget, m_texture);
      
      glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
      glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
      
      glTexImage2D(textureTarget, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
      
    }
}

Texture::~Texture()
{
  glDeleteTextures(1, &m_texture);
}

void Texture::bind(unsigned unit)
{
  assert(unit >= 0 && unit <= 31);

  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, m_texture);


}
