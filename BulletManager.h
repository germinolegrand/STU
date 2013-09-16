#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "using.h"
#include <memory>
#include <map>

#include "TextureManager.h"

class Bullet
{
public:
    Bullet(TextureManager textures, sf::Vector2f position, std::function<sf::Vector2f(sf::Time, const sf::Vector2f&)> animation);

    void animate(sf::Time clock);

private:
    TextureManager m_textures;

    sf::Sprite m_sprite;

    std::function<sf::Vector2f(sf::Time, const sf::Vector2f&)> m_animation;

    friend void draw(Renderer &ren, const Bullet &bullet);
    friend sf::FloatRect getCollisionBox(Bullet& b){ return b.m_sprite.getGlobalBounds(); }
};

void draw(Renderer &ren, const Bullet &bullet);


class BulletManager
{
private:
    TextureManager m_textures;
    std::multimap<sf::Time, Bullet> m_bullets;

public:
    BulletManager(TextureManager textures);

    void createBullet(sf::Time clock, const std::string &type, sf::Vector2f position, std::function<sf::Vector2f(sf::Time, const sf::Vector2f&)> animation);
    void clearBullets();

    void erase(Bullet& bullet);

    void animateBullets(sf::Time clock);

    struct iterator
    {
        iterator operator++(){ ++m_it; return *this; }
        Bullet& operator*(){ return m_it->second; }
        friend bool operator!=(iterator& a, iterator& b){ return a.m_it != b.m_it; }

    private:
        decltype(m_bullets)::iterator m_it;
        friend iterator begin(BulletManager& b);
        friend iterator end(BulletManager& b);
        iterator(decltype(m_it) it): m_it(it){}
    };

private:
    friend void draw(Renderer &ren, const BulletManager &bullets);
    friend iterator begin(BulletManager& b){ return iterator{begin(b.m_bullets)}; }
    friend iterator end(BulletManager& b){ return iterator{end(b.m_bullets)}; }
};

void draw(Renderer &ren, const BulletManager &bullets);

#endif // BULLETMANAGER_H
