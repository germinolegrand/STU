#include "MonsterControler.h"

#include "Monster.h"
#include "BulletManager.h"

MonsterControler::MonsterControler(sf::Time clock, Monster& monster, std::function<void()> explode, BulletManager& bulletManager):
    m_clock(clock),
    m_monster(monster),
    m_explode(explode),
    m_bulletManager(bulletManager)
{
    //ctor
}

void MonsterControler::move(const sf::Vector2f& offset)
{
    m_monster.move(offset);
}

void MonsterControler::explode()
{
    m_explode();
}

void MonsterControler::spawnBullet(const std::string& type, animation::BulletAnimation animation)
{
    m_bulletManager.spawnBullet(m_clock, type, getBulletCreationPoint(m_monster), animation);
}
