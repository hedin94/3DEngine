#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
 public:
  Texture(const std::string& filename);
  Texture(int width = 0, int height = 0, unsigned char* data = 0, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR, GLint internalFormat = GL_RGBA, GLenum format = GL_RGBA, bool clamp = false);
  virtual ~Texture();

  void bind(unsigned unit);

  GLuint getTexture() { return m_texture; }

 private:
  GLuint m_texture;

};
#endif // TEXTURE_H
