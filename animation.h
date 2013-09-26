#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED

#include <cmath>
#include <complex>

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


inline sf::Vector2f moveAroundCircle(sf::Time t, sf::Time prev_t)
{
    auto prev_pos = std::polar(50.f, prev_t.asSeconds());
    auto pos = std::polar(50.f, t.asSeconds());
    return{real(pos) - real(prev_pos), imag(pos) - imag(prev_pos)};
}

}

#endif // ANIMATION_H_INCLUDED
