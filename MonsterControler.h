#ifndef MONSTERCONTROLER_H
#define MONSTERCONTROLER_H

#include <functional>
#include "using.h"
#include "animation.h"

class Monster;
class BulletManager;

class MonsterControler
{
public:
    MonsterControler(sf::Time clock, Monster& monster, std::function<void()> explode, BulletManager& bulletManager);

    void move(const sf::Vector2f& offset);
    void explode();
    void spawnBullet(const std::string& type, animation::BulletAnimation animation);

private:
    sf::Time m_clock;

    Monster& m_monster;
    std::function<void()> m_explode;
    BulletManager& m_bulletManager;
};

#endif // MONSTERCONTROLER_H
