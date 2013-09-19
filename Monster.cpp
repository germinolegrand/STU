#include "Monster.h"

Monster::Monster(TextureManager textures):
    m_textures(textures),
    m_sprite(textures["normal"])
{
    //ctor
}

void draw(Renderer& ren, const Monster& monster)
{
    ren.draw(monster.m_sprite);
}

sf::FloatRect getCollisionBox(const Monster& monster)
{
    return monster.m_sprite.getGlobalBounds();
}
