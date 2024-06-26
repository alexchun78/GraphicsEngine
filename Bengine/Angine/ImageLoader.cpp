#include "ImageLoader.h"
#include "picoPNG.h"
#include "IOManager.h"
#include "Errors.h"

GLTexture ImageLoader::loadPNG(std::string filePath)
{
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;
	
	if (IOManager::ReadFileToBuffer(filePath, in) == false)
	{
		FatalError("Failed to load PNG file to buffer");
	}

	int errorCode = Bengine::decodePNG(out, width, height, &(in[0]),in.size());
	if (errorCode != 0)
	{
		FatalError("DecodePNG failed with error : " + std::to_string(errorCode));
	}

	// opengl 텍스처 생성
	glGenTextures(1, &(texture._id));

	glBindTexture(GL_TEXTURE_2D, texture._id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	texture._width = width;
	texture._height = height;

	return texture;
}
