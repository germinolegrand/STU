#include "GameInputEventProcessor.h"

#include "Game.h"
#include "animation.h"

GameInputEventProcessor::GameInputEventProcessor(Game &ga): m_ga(ga)
{
    //ctor
}

GameInputEventProcessor::~GameInputEventProcessor()
{
    //dtor
}

bool GameInputEventProcessor::processInput(sf::Event& ev)
{
    if(ev.type == sf::Event::EventType::KeyPressed)
    {
        if(ev.key.code == sf::Keyboard::Key::P)
        {
            if(m_pauseOnPush)
                m_ga.pauseSwitch();

            m_pauseOnPush = false;
            return true;
        }
        else if(ev.key.code == sf::Keyboard::Key::LShift)
        {
            m_ga.m_heroController.slowDown(true);
        }
        else if(ev.key.code == sf::Keyboard::Key::W)
        {
            m_ga.m_ally_bullets.createBullet(m_ga.getClock(), "ally/", getBulletCreationPoint(m_ga.m_firstHeroEver), animation::goUp(1000.f));
        }
    }
    else if(ev.type == sf::Event::EventType::KeyReleased)
    {
        if(ev.key.code == sf::Keyboard::Key::P)
        {
            m_pauseOnPush = true;
            return true;
        }
        else if(ev.key.code == sf::Keyboard::Key::LShift)
        {
            m_ga.m_heroController.slowDown(false);
        }
    }

    return false;
}
