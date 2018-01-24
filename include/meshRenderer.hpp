#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "mesh.hpp"
#include "texture.hpp"
#include "material.hpp"
#include "shader.hpp"
#include "gameComponent.hpp"
#include "debug.hpp"

#include <iostream>

class MeshRenderer : public GameComponent
{
 public:
  MeshRenderer(Mesh* mesh, Material* material)
    : m_mesh(mesh), m_material(material) {};

  virtual ~MeshRenderer();
  
  virtual void input(float delta) override;
  virtual void update(float delta) override;
  virtual void render(Shader* shader, RenderingEngine* renderingEngine) override;

  virtual void setParent(GameObject* parent) override { GameComponent::setParent(parent); }
 private:
  Mesh* m_mesh;
  Material* m_material;
};
#endif //MESH_RENDERER_H
