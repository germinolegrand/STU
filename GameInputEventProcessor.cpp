#include "GameInputEventProcessor.h"

#include "Game.h"

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
            m_ga.pauseSwitch();
            return true;
        }
    }

    return false;
}
