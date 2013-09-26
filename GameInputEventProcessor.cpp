#include "GameInputEventProcessor.h"

#include "Game.h"
#include "animation.h"

GameInputEventProcessor::GameInputEventProcessor(Game &ga): m_ga(ga)
{
    m_ga.heroBulletSpawning(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
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
        else if(ev.key.code == sf::Keyboard::Key::LControl)
        {
            m_ga.slowDown(true);
        }
        else if(ev.key.code == sf::Keyboard::Key::W)
        {
            m_ga.heroBulletSpawning(true);
        }
        else if(m_ga.m_state == Game::State::Menu || m_ga.m_state == Game::State::Paused)
        {
            if(ev.key.code == sf::Keyboard::Key::Down)
            {
                m_ga.m_current_menu->highlightNextEntry();
            }
            else if(ev.key.code == sf::Keyboard::Key::Up)
            {
                m_ga.m_current_menu->highlightPrevEntry();
            }
            else if(ev.key.code == sf::Keyboard::Key::Return)
            {
                m_ga.m_current_menu->selectEntry();
            }
        }
    }
    else if(ev.type == sf::Event::EventType::KeyReleased)
    {
        if(ev.key.code == sf::Keyboard::Key::P)
        {
            m_pauseOnPush = true;
            return true;
        }
        else if(ev.key.code == sf::Keyboard::Key::LControl)
        {
            m_ga.slowDown(false);
        }
        else if(ev.key.code == sf::Keyboard::Key::W)
        {
            m_ga.heroBulletSpawning(false);
        }
    }

    return false;
}
