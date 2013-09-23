#include "MonsterManager.h"

#include <algorithm>
#include <complex>

MonsterManager::MonsterManager(TextureManager textures):
    m_textures(textures)
{
    //ctor
}

void MonsterManager::spawnMonster(sf::Time clock, const std::string& type, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation)
{
    m_monsters.insert(decltype(m_monsters)::value_type(clock, Monster{m_textures.subTextures(type), position, animation}));
}

void MonsterManager::animateMonsters(sf::Time clock, sf::Time prev_clock, BulletManager& bulletManager)
{
    std::vector<decltype(m_monsters)::iterator> to_erase;

    for(auto it = begin(m_monsters); it != end(m_monsters); ++it)
    {
        auto& monster = *it;

        monster.second.animate(clock - monster.first, prev_clock - monster.first, MonsterControler{clock, monster.second, [&to_erase, it](){ to_erase.push_back(it); }, bulletManager});

        auto BBox = getCollisionBox(monster.second);

        if(BBox.left < -static_cast<int>(videoMode.width)/2 || BBox.top < -static_cast<int>(videoMode.height)/2 || BBox.left > videoMode.width*1.5f || BBox.top > videoMode.height*1.5f)
            to_erase.push_back(it);
    }

    for(auto monster : to_erase)
        m_monsters.erase(monster);
}

void draw(Renderer& ren, const MonsterManager& monsters)
{
    for(const auto& monster : monsters.m_monsters)
        draw(ren, monster.second);
}
