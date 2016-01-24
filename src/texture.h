#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
 public:
  Texture(const std::string& filename);
  virtual ~Texture();

  void bind(unsigned unit);

  GLuint getTexture() { return m_texture; }

 private:
  GLuint m_texture;
};
#endif // TEXTURE_H
