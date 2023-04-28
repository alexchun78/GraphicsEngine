#include "Errors.h"
#include <iostream>
#include <vector>
#include <SDL/SDL.h>

void FatalError(std::string errorString)
{
	std::cout << errorString << std::endl;
	std::cout << "Enter any key to quit...";
	int tmp;
	std::cin >> tmp;
	SDL_Quit();
}

void ShaderCompileError(const std::string& filePath, GLuint shaderID)
{
    GLint success = 0;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logSize = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
        // The maxLength includes the NULL character
        std::vector<char> errorLog(logSize);
        glGetShaderInfoLog(shaderID, logSize, &logSize, &errorLog[0]);

        // Provide the infolog in whatever manor you deem best.
        // Exit with failure.
        glDeleteShader(shaderID); // Don't leak the shader.
        std::printf("%s\n", &(errorLog[0]));
        FatalError("shader " + filePath +" failed to compile.");
    }
}

void ShaderLinkError(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<char> infoLog(maxLength);
        glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(programID);
        // Don't leak shaders either.
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        // Use the infoLog as you see fit.
        std::printf("%s\n", &(infoLog[0]));
        FatalError("link failed to compile.");
    }
}
