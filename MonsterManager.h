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

    Monster operator[](const std::string &type);

private:
    std::map<std::string, Monster> m_monsters;
};

#endif // MONSTERMANAGER_H
