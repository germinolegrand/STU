#include "BulletManager.h"

Bullet::Bullet(TextureManager textures, sf::Vector2f position, animation::BulletAnimation animation):
    m_textures(textures),
    m_sprite(m_textures["1"]),
    m_animation(animation)
{
    m_sprite.setPosition(position);
}

void Bullet::animate(sf::Time clock, sf::Time prev_clock)
{
    m_sprite.setPosition(m_animation(clock, prev_clock, m_sprite.getPosition()));
}

void draw(Renderer& ren, const Bullet& bullet)
{
    draw(ren, bullet.m_sprite);
}

int getDamages(Bullet& b)
{
    return 1;
}


BulletManager::BulletManager(TextureManager textures):
    m_textures(textures)
{
    //ctor
}

void BulletManager::spawnBullet(sf::Time clock, const std::string& type, sf::Vector2f position, animation::BulletAnimation animation)
{
    m_bullets.insert(decltype(m_bullets)::value_type{clock, Bullet{m_textures.subTextures(type), position, animation}});
}

void BulletManager::clearBullets()
{
    m_bullets.clear();
}

void BulletManager::erase(Bullet& bullet)
{
    m_bullets.erase(find_if(begin(m_bullets), end(m_bullets), [&bullet](decltype(m_bullets)::value_type& b){ return &bullet == &b.second; }));
}

void BulletManager::animateBullets(sf::Time clock, sf::Time prev_clock)
{
    std::vector<Bullet*> out_of_field;

    for(auto& bullet : m_bullets)
    {
        bullet.second.animate(clock - bullet.first, prev_clock - bullet.first);

        auto BBox = getCollisionBox(bullet.second);

        if(BBox.left < -static_cast<int>(videoMode.width)/2 || BBox.top < -static_cast<int>(videoMode.height)/2 || BBox.left > videoMode.width*1.5f || BBox.top > videoMode.height*1.5f)
            out_of_field.push_back(&bullet.second);
    }

    for(auto& bullet : out_of_field)
        erase(*bullet);
}


void draw(Renderer& ren, const BulletManager& bullets)
{
    for(const auto& bullet : bullets.m_bullets)
        draw(ren, bullet.second);
}

