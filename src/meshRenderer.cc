#include "meshRenderer.h"
void
MeshRenderer::
input(float delta)
{
  //DEBUG("MeshRenderer::input");
}

void
MeshRenderer::
update(float delta)
{
  //DEBUG("MeshRenderer::update");
}


void
MeshRenderer::
render(Shader* shader, RenderingEngine* renderingEngine)
{
    shader->bind();
    //m_material->getTexture("diffuse")->bind(0);
    //m_material->getTexture("normalMap")->bind(1);
    //DEBUG("MeshRenderer::render");
    shader->update(getTransform(), renderingEngine, m_material);
    m_mesh->draw();
}
