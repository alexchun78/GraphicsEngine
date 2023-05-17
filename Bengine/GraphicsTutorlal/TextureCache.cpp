#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
TextureCache::TextureCache()
{

}
TextureCache::~TextureCache()
{

}

GLTexture TextureCache::getTexture(std::string texturePath)
{
    auto iter = m_textureMap.find(texturePath);
    if (iter == m_textureMap.end())
    {
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        m_textureMap.insert(std::make_pair(texturePath, newTexture));

        std::cout << "Loaded cached texture\n";
        return newTexture;
    }
    return iter->second;
}