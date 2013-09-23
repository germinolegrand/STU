#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <cmath>

namespace animation
{

using BulletAnimation = std::function<sf::Vector2f(sf::Time, sf::Time, const sf::Vector2f&)>;

inline BulletAnimation goStraight(sf::Vector2f speed)
{
    return [speed](sf::Time t, sf::Time prev_t, const sf::Vector2f& pos)
    {
        return pos + speed*(t - prev_t).asSeconds();
    };
}

}

#endif // ANIMATION_H_INCLUDED
