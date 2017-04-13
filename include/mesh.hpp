#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include "obj_loader.hpp"

class Vertex
{
public:
  Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal = glm::vec3(0,0,0), const glm::vec3& tangent = glm::vec3(0,0,0))
   : m_pos(pos), m_texCoord(texCoord), m_normal(normal), m_tangent(tangent){}

private:
  glm::vec3 m_pos;
  glm::vec2 m_texCoord;
  glm::vec3 m_normal;
  glm::vec3 m_tangent;

  friend class Mesh;
};


class Mesh
{
public:
  Mesh(Vertex* vertices, unsigned numVertices, unsigned* indices, unsigned numIndices);
  Mesh(const std::string& filename);
  virtual ~Mesh();

  void draw();
  void initMesh(const IndexedModel& model);

private:
enum
  {
    POSITION_VB,
    TEXCOORD_VB,
    NORMAL_VB,
    TANGENT_VB,

    INDEX_VB,

    NUM_BUFFERS
  };
  GLuint m_vertexArrayObject;
  GLuint m_vertexArrayBuffers[NUM_BUFFERS];
  unsigned m_drawCount;
};
#endif // MESH_H
