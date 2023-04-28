#include "GLSLProgram.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : m_nAttrIndex(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0)
{    
}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
{
    // link : https://www.khronos.org/opengl/wiki/Shader_Compilation
    // section : Shader object compilation
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0)
    {
        FatalError("vertex shader failed to created.");
    }
    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_vertexShaderID == 0)
    {
        FatalError("fragment shader failed to created.");
    }

    // compile vertex shader
    CompileShader(vertexShaderFilePath, m_vertexShaderID);
    // compile fagment shader
    CompileShader(fragmentShaderFilePath, m_fragmentShaderID);


}

void GLSLProgram::CompileShader(const std::string& filePath, GLuint& id)
{
    std::ifstream file(filePath);
    if (file.fail())
    {
        FatalError("Faile to open" + filePath);
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(file, line))
    {
        fileContents += line + "\n";
    }

    file.close();
    const char* ptrContens = fileContents.c_str();
    glShaderSource(id, 1, &ptrContens, nullptr);

    glCompileShader(id);
    ShaderCompileError(filePath,id);
}

void GLSLProgram::AddAttibutes(const std::string& attrName)
{
    glBindAttribLocation(m_programID, m_nAttrIndex++, attrName.c_str());
}

void GLSLProgram::LinkShader()
{
    // Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
    m_programID = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    // Link our program
    glLinkProgram(m_programID);
    ShaderLinkError(m_programID, m_vertexShaderID, m_fragmentShaderID);

    // Always detach shaders after a successful link.
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::Use()
{
    glUseProgram(m_programID);
    for (int i = 0; i < m_nAttrIndex;++i)
    {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::UnUse()
{
    glUseProgram(0);
    for (int i = 0; i < m_nAttrIndex;++i)
    {
        glDisableVertexAttribArray(i);
    }
}

