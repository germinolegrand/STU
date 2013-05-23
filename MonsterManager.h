#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include "using.h"

#include <map>
#include <memory>

#include "Monster.h"

class MonsterManager
{
public:
    MonsterManager();
    virtual ~MonsterManager();

    Monster& createMonster(const std::string &type);
    void deleteMonster(Monster &monster);

private:
    std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
    std::vector<std::unique_ptr<Monster>> m_monsters;
};

#endif // MONSTERMANAGER_H
