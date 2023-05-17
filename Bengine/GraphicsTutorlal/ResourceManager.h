#pragma once
#include "TextureCache.h"
#include <string>
class ResourceManager
{
public:
    static GLTexture GetTexture(std::string texturePath);
    //static GLuint m_boundTexture;
private:
    static TextureCache m_textureCache;
};

