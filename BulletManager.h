#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#include "using.h"
#include <memory>

#include "TextureManager.h"

struct Bullet
{
    sf::Sprite sprite;
    std::function<sf::Vector2f(const sf::Vector2f&)> animation;
};


class BulletManager
{
public:
    BulletManager(TextureManager textures);
    virtual ~BulletManager();

    void createBullet(bool isAlly, const std::string &type, sf::Vector2f position, std::function<sf::Vector2f(const sf::Vector2f&)> animation);
    void clearBullets();

private:
    TextureManager m_textures;
    std::vector<std::unique_ptr<Bullet>> m_annemyBullets,
                                         m_allyBullets;
};

#endif // BULLETMANAGER_H
