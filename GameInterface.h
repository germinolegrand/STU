#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include <SFML/Graphics.hpp>

class Game;

class GameInterface
{
public:
    GameInterface(Game &ga);

private:
    Game &m_ga;

    sf::Font m_font;

    sf::Text m_dialogBox;
};

#endif // GAMEINTERFACE_H
