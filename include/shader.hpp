#ifndef SHADER_H
#define SHADER_H

#include "transform.hpp"
#include "material.hpp"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <GL/glew.h>
#include <glm/glm.hpp>

class RenderingEngine;
class BaseLight;
class DirectionalLight;
class PointLight;
class SpotLight;

struct UniformData
{
    UniformData() = default;
    UniformData(const GLuint& loc, const std::string& t, const bool& is = false)
	: location(loc), type(t), insideStruct(is) {}

    GLuint location;
    std::string type;
    bool insideStruct;
};

class Shader
{
public:
    using uniform_structs = std::map<std::string, std::vector<std::pair<std::string, std::string> > >;

    Shader(const std::string& filename);
    virtual ~Shader();
 
    void bind();
    virtual void update(Transform* transform, RenderingEngine* engine, Material* material);
    void compileShader();

    void addUniform(const std::string& uniformName, const std::string& uniformType, const bool& = false);
    void addUniformsFromFile(const std::string& filename);
    void addAttributesFromFile(const std::string& filename);

    void addVertexShaderFromFile(const std::string& text);
    void addGeometryShaderFromFile(const std::string& text);
    void addFragmentShaderFromFile(const std::string& text);
    void addVertexShader(const std::string& text);
    void addGeometryShader(const std::string& text);
    void addFragmentShader(const std::string& text);

    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniformV(const std::string& name, float* value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::mat4& value);

    void setUniform(const std::string& name, BaseLight* baseLight);
    void setUniform(const std::string& name, DirectionalLight* directionalLight);
    void setUniform(const std::string& name, PointLight* PointLight);
    void setUniform(const std::string& name, SpotLight* spotLight);

protected:
    GLuint m_program;

private:

    std::vector<GLuint> m_shaders;
    std::unordered_map<std::string, UniformData> m_uniforms;

    GLuint createShader(const std::string& text, GLenum shaderType);
    uniform_structs findUniformStructs(const std::string& shaderText);
    void addUniformWithCheck(const std::string& type, const std::string& name, uniform_structs structs);

};

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);

#endif // SHADER_H
