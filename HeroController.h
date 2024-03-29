#ifndef HEROCONTROLLER_H
#define HEROCONTROLLER_H

#include <SFML/System.hpp>

class Hero;

class HeroController
{
public:
    HeroController();
    virtual ~HeroController();

    void controlHero(sf::Time clock, sf::Time prev_clock, Hero &hero);

    void slowDown(bool sld);

private:
    float m_normalSpeed = 400.f;
    float m_slowSpeed = 150.f;
    float m_speed = m_normalSpeed;
};

#endif // HEROCONTROLLER_H
