#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>
#include "Errors.h"

class GLSLProgram
{
public:

    GLSLProgram();
    ~GLSLProgram();

    void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
    void CompileShader(const std::string& filePath, GLuint& id);
    void AddAttibutes(const std::string& attrName);
    void LinkShader();

    GLuint GetUniformLocation(const std::string& uniformName);

    void Use();
    void UnUse();

private:
    int m_nAttrIndex;
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};
#endif // GLSLPROGRAM_H
