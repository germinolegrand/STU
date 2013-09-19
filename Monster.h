#ifndef MONSTER_H
#define MONSTER_H

#include "using.h"
#include "TextureManager.h"

class Monster
{
public:
    Monster(TextureManager textures);

private:
    TextureManager m_textures;
    sf::Sprite m_sprite;

friend void draw(Renderer &ren, const Monster &monster);
friend sf::FloatRect getCollisionBox(const Monster& monster);
};

#endif // MONSTER_H
