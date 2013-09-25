#include "Monster.h"

Monster::Monster(TextureManager textures, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life):
    m_textures(textures),
    m_sprite(textures["normal"]),
    m_animation(animation),
    m_life(life)
{
    m_sprite.setPosition(position);
}

void Monster::move(const sf::Vector2f& offset)
{
    m_sprite.move(offset);
}

void Monster::animate(sf::Time clock, sf::Time prev_t, MonsterControler mc)
{
    if(!isAlive(m_life))
        mc.explode();

    m_animation(clock, prev_t, std::move(mc));
}


void draw(Renderer& ren, const Monster& monster)
{
    draw(ren, monster.m_sprite);
    draw(ren, monster.m_life, sf::Vector2f(monster.m_sprite.getGlobalBounds().left, monster.m_sprite.getGlobalBounds().top + monster.m_sprite.getLocalBounds().height));
}

sf::FloatRect getCollisionBox(const Monster& monster)
{
    return monster.m_sprite.getGlobalBounds();
}

sf::Vector2f getBulletCreationPoint(const Monster& monster)
{
    return monster.m_sprite.getPosition() + sf::Vector2f{monster.m_sprite.getLocalBounds().width/2, monster.m_sprite.getLocalBounds().height};
}

int getDamages(Monster& m)
{
    return 2;
}

void takeDamages(Monster& m, int damages)
{
    m.m_life -= damages;
}
