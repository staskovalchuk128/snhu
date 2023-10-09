#pragma once
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();
    // activate the shader
    // ------------------------------------------------------------------------
    void Bind();
    // utility uniform functions
    // ------------------------------------------------------------------------
    void SetBool(const std::string& name, bool value);
    void SetInt(const std::string& name, int value);
    void SetFloat(const std::string& name, float value);
    void SetVec2(const std::string& name, const glm::vec2& value);
    void SetVec3(const std::string& name, const glm::vec3& value);
    void SetVec4(const std::string& name, const glm::vec4& value);
    void SetMat4(const std::string& name, const glm::mat4& mat);
private:
    unsigned int ID;
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void CheckCompileErrors(int shader, std::string type);
};
