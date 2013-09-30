#ifndef MONSTER_H
#define MONSTER_H

#include "using.h"
#include "TextureManager.h"
#include "MonsterControler.h"
#include "Life.h"

class Monster
{
public:
    Monster(TextureManager textures, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life, std::function<void()> onDeath = nullptr);
    ~Monster();

    Monster(Monster&&) = default;

    void move(const sf::Vector2f& offset);
    void animate(sf::Time t, sf::Time prev_t, MonsterControler mc);

private:
    TextureManager m_textures;
    sf::Sprite m_sprite;

    std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> m_animation;
    std::function<void()> m_onDeath;

    Life m_life;

friend void draw(Renderer &ren, const Monster &monster);
friend sf::FloatRect getCollisionBox(const Monster& monster);
friend sf::Vector2f getBulletCreationPoint(const Monster& monster);
friend int getDamages(Monster& m);
friend void takeDamages(Monster& m, int damages);
};

#endif // MONSTER_H
