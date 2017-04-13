#include "mesh.hpp"
#include <vector>
#include <cassert>
#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::Mesh(Vertex* vertices, unsigned numVertices , unsigned* indices, unsigned numIndices)
{
    
  IndexedModel model;

  for(unsigned i = 0; i < numVertices; i++)
    {
      model.positions.push_back(vertices[i].m_pos);
      model.texCoords.push_back(vertices[i].m_texCoord);
      model.normals.push_back(vertices[i].m_normal);
      //model.tangents.push_back(vertices[i].m_tangent);
    }

  model.CalcTangents();

  for(unsigned i = 0; i < numIndices; i++)
    {
      model.indices.push_back(indices[i]);
    }
  
  initMesh(model);
}

Mesh::Mesh(const std::string& filename)
{
  IndexedModel indexedModel; //= OBJModel("./res/models/" + filename).ToIndexedModel();

  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(("./res/models/" + filename).c_str(), 
					   aiProcess_Triangulate |
					   aiProcess_GenSmoothNormals | 
					   aiProcess_FlipUVs |
					   aiProcess_CalcTangentSpace);
		
  if(!scene)
    {
      std::cout << "Mesh load failed!: " << filename << std::endl;
      assert(0 == 0);
    }


  const aiMesh* model = scene->mMeshes[0];
  // std::cout << "Meshes: " << scene->mNumMeshes << std::endl;
  // std::cout << "Vertices: " << model->mNumVertices << std::endl;
  // std::cout << "Faces: " << model->mNumFaces << std::endl;
  // std::cout << "Has normals: " << model->HasNormals() << std::endl;
  // std::cout << "Has tangents: " << model->HasTangentsAndBitangents() << std::endl;
  
  const aiVector3D aiZeroVector(0.0f, 0.0f, 0.0f);
  for(unsigned int i = 0; i < model->mNumVertices; i++) 
    {
      glm::vec3 pos(model->mVertices[i].x, model->mVertices[i].y, model->mVertices[i].z);

      glm::vec2 texCoords(0.0f, 0.0f);
      if(model->HasTextureCoords(0))
        texCoords = glm::vec2(model->mTextureCoords[0][i].x, model->mTextureCoords[0][i].y);

      glm::vec3 normal(model->mNormals[i].x, model->mNormals[i].y, model->mNormals[i].z);
      
      glm::vec3 tangent(0.0f, 0.0f, 0.0f);
      if(model->HasTangentsAndBitangents())
	tangent = glm::vec3(model->mTangents[i].x, model->mTangents[i].y, model->mTangents[i].z); 

      indexedModel.positions.push_back(pos);
      indexedModel.texCoords.push_back(texCoords);
      indexedModel.normals.push_back(normal);
      indexedModel.tangents.push_back(tangent);
    }

  for(unsigned int i = 0; i < model->mNumFaces; i++)
    {
      const aiFace& face = model->mFaces[i];
      assert(face.mNumIndices == 3);
      indexedModel.indices.push_back(face.mIndices[0]);
      indexedModel.indices.push_back(face.mIndices[1]);
      indexedModel.indices.push_back(face.mIndices[2]);
    }

  //indexedModel.indices = indices;

  initMesh(indexedModel);
}

Mesh::~Mesh()
{
  glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::draw()
{
  glBindVertexArray(m_vertexArrayObject);
  glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

  glBindVertexArray(0);
}

void Mesh::initMesh(const IndexedModel& model)
{
  m_drawCount = model.indices.size();

  glGenVertexArrays(1, &m_vertexArrayObject);
  glBindVertexArray(m_vertexArrayObject);

  glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.positions.size()*sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.normals.size()*sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TANGENT_VB]);
  glBufferData(GL_ARRAY_BUFFER, model.tangents.size()*sizeof(model.tangents[0]), &model.tangents[0], GL_STATIC_DRAW);
  
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size()*sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
}
