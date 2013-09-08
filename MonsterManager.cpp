#include "MonsterManager.h"

#include <algorithm>

MonsterManager::MonsterManager(TextureManager textures)
{
    m_monsters.emplace("planemonster", Monster{textures.subTextures("planemonster/")});
}

Monster MonsterManager::operator[](const std::string& type)
{
    return m_monsters.at(type);
}

