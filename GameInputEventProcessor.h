#ifndef GAMEINPUTEVENTPROCESSOR_H
#define GAMEINPUTEVENTPROCESSOR_H

#include <SFML/Window.hpp>

class Game;

class GameInputEventProcessor
{
public:
    GameInputEventProcessor(Game& ga);

    bool processInput(sf::Event &ev);

private:
    Game &m_ga;

    bool m_pauseOnPush = !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);
};

#endif // GAMEINPUTEVENTPROCESSOR_H
