#include "ResourceManager.h"

// private static member �̱� ������ �� ������.
TextureCache ResourceManager::m_textureCache;

GLTexture ResourceManager::GetTexture(std::string texturePath)
{
    return m_textureCache.getTexture(texturePath);
}