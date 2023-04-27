#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:

    GLSLProgram();
    ~GLSLProgram();

    void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void LinkShader();

private:
    GLuint m_programID;
    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};
#endif // GLSLPROGRAM_H
