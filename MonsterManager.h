#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include "using.h"

#include <map>
#include <memory>

#include "Monster.h"
#include "TextureManager.h"

class BulletManager;

class MonsterManager
{
private:
    TextureManager m_textures;
    std::multimap<sf::Time, Monster> m_monsters;

public:
    MonsterManager(TextureManager textures);

    void clearMonsters();

    void spawnMonster(sf::Time clock, const std::string& type, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life, std::function<void()> onDeath = nullptr);

    void animateMonsters(sf::Time clock, sf::Time prev_clock, BulletManager& bulletManager);

    struct iterator
    {
        iterator operator++(){ ++m_it; return *this; }
        Monster& operator*(){ return m_it->second; }
        friend bool operator!=(iterator& a, iterator& b){ return a.m_it != b.m_it; }

    private:
        decltype(m_monsters)::iterator m_it;
        friend iterator begin(MonsterManager& b);
        friend iterator end(MonsterManager& b);
        iterator(decltype(m_it) it): m_it(it){}
        friend size_t distance(const iterator& a, const iterator& b){ return distance(a.m_it, b.m_it); }
    };

private:
    friend void draw(Renderer &ren, const MonsterManager &monsters);
    friend iterator begin(MonsterManager& b){ return iterator{begin(b.m_monsters)}; }
    friend iterator end(MonsterManager& b){ return iterator{end(b.m_monsters)}; }
};

#endif // MONSTERMANAGER_H
