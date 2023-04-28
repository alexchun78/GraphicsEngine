#ifndef ERRORS_H
#define ERRORS_H
#include <string>
#include <GL/glew.h>

extern void FatalError(std::string errorString);
extern void ShaderCompileError(const std::string& filePath, GLuint shaderID);
extern void ShaderLinkError(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID);

#endif //ERRORS_H 