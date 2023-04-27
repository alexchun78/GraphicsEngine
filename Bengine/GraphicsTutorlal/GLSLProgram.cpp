#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
{    
}

GLSLProgram::~GLSLProgram()
{

}

void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
}

void GLSLProgram::LinkShader()
{

}


