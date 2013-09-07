#ifndef MONSTERMANAGER_H
#define MONSTERMANAGER_H

#include "using.h"

#include <map>
#include <memory>

#include "Monster.h"
#include "TextureManager.h"

class MonsterManager
{
public:
    MonsterManager(TextureManager textures);
    virtual ~MonsterManager();

    Monster& createMonster(const std::string &type);
    void deleteMonster(Monster &monster);

private:
    TextureManager m_textures;
    std::vector<std::unique_ptr<Monster>> m_monsters;
};

#endif // MONSTERMANAGER_H
