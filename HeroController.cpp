#include "HeroController.h"

#include "Hero.h"

#include <SFML/Window.hpp>

HeroController::HeroController()
{
    //ctor
}

HeroController::~HeroController()
{
    //dtor
}

void HeroController::controlHero(const sf::Time &clock, Hero &hero)
{
    sf::Vector2f movement;
    sf::Time timelaps(clock - m_moveClock);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        movement.x += m_speed*timelaps.asSeconds();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        movement.x -= m_speed*timelaps.asSeconds();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        movement.y += m_speed*timelaps.asSeconds();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        movement.y -= m_speed*timelaps.asSeconds();
    }

    hero.move(movement);

    m_moveClock = clock;
}

void HeroController::slowDown(bool sld)
{
    m_speed = sld ? m_slowSpeed : m_normalSpeed;
}
