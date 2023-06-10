#include "ResourceManager.h"

// private static member 이기 때문에 꼭 가능함.
TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
    return m_textureCache.getTexture(texturePath);
}