#include "Monster.h"

Monster::Monster(TextureManager textures, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation):
    m_textures(textures),
    m_sprite(textures["normal"]),
    m_animation(animation)
{
    m_sprite.setPosition(position);
}

void Monster::move(const sf::Vector2f& offset)
{
    m_sprite.move(offset);
}

void Monster::animate(sf::Time clock, sf::Time prev_t, MonsterControler mc)
{
    m_animation(clock, prev_t, std::move(mc));
}


void draw(Renderer& ren, const Monster& monster)
{
    ren.draw(monster.m_sprite);
}

sf::FloatRect getCollisionBox(const Monster& monster)
{
    return monster.m_sprite.getGlobalBounds();
}

sf::Vector2f getBulletCreationPoint(const Monster& monster)
{
    return monster.m_sprite.getPosition() + sf::Vector2f{monster.m_sprite.getLocalBounds().width/2, monster.m_sprite.getLocalBounds().height};
}
