#ifndef HEROCONTROLLER_H
#define HEROCONTROLLER_H

#include <SFML/System.hpp>

class Hero;

class HeroController
{
public:
    HeroController();
    virtual ~HeroController();

    void controlHero(const sf::Time &clock, Hero &hero);

    void slowDown(bool sld);

private:
    float m_slowSpeed = 0.5f;
    float m_horizontalSpeed = 400.f;
    float m_verticalSpeed = 400.f;

    sf::Time m_moveClock;
};

#endif // HEROCONTROLLER_H
