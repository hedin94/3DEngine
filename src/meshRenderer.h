#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "mesh.h"
#include "texture.h"
#include "material.h"
#include "shader.h"
#include "phongShader.h"
#include <iostream>
#include "debug.h"

class MeshRenderer : public GameComponent
{
 public:
  MeshRenderer(Mesh* mesh, Material* material)
    : m_mesh(mesh), m_material(material) {};

  ~MeshRenderer()
  {
    if(m_mesh)
      delete m_mesh;
    if(m_material)
      delete m_material;
  }

  virtual void input(float delta) override;
  virtual void update(float delta) override;
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) override;

  virtual void setParent(GameObject* parent) override { GameComponent::setParent(parent); }
 private:
  Mesh* m_mesh;
  Material* m_material;
};
#endif //MESH_RENDERER_H
