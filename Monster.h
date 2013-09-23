#ifndef MONSTER_H
#define MONSTER_H

#include "using.h"
#include "TextureManager.h"
#include "MonsterControler.h"

class Monster
{
public:
    Monster(TextureManager textures, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation);

    void move(const sf::Vector2f& offset);
    void animate(sf::Time t, sf::Time prev_t, MonsterControler mc);

private:
    TextureManager m_textures;
    sf::Sprite m_sprite;

    std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> m_animation;

friend void draw(Renderer &ren, const Monster &monster);
friend sf::FloatRect getCollisionBox(const Monster& monster);
friend sf::Vector2f getBulletCreationPoint(const Monster& monster);
};

#endif // MONSTER_H
