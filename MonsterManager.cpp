#include "MonsterManager.h"

#include <algorithm>

MonsterManager::MonsterManager(TextureManager textures):
    m_textures(textures)
{
    //ctor
}

MonsterManager::~MonsterManager()
{
    //dtor
}

Monster& MonsterManager::createMonster(const std::string& type)
{
    std::unique_ptr<Monster> mst(new Monster(m_textures[type]));

    m_monsters.push_back(std::move(mst));

    return *m_monsters.back();
}

void MonsterManager::deleteMonster(Monster& monster)
{
    m_monsters.erase(std::find_if(begin(m_monsters), end(m_monsters), [&monster](const std::unique_ptr<Monster> &mst)
    {
        return &monster == mst.get();
    }));
}
