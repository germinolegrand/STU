#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <cmath>
#include <iostream>

namespace animation
{

using Animation = std::function<sf::Vector2f(sf::Time, const sf::Vector2f&)>;

Animation goUp(float speed)
{
    sf::Time previous = sf::Time::Zero;
    return [speed, previous](sf::Time t, const sf::Vector2f& pos) mutable
    {
        auto newpos = pos + sf::Vector2f{0, -speed*(t - previous).asSeconds()};
        previous = t;
        return newpos;
    };
}

}

#endif // ANIMATION_H_INCLUDED
