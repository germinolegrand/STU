#ifndef GAME_H
#define GAME_H

#include "using.h"
#include <SFML/Audio.hpp>

#include "Hero.h"
#include "HeroController.h"

#include "Background.h"

class Game
{
public:
    Game();
    virtual ~Game();

    void pause(bool pauseOn);
    bool pauseSwitch();

    void frame();

protected:
private:
    Hero m_firstHeroEver {"heros_bidon.png"};
    HeroController m_heroController;

    Background m_bg;

    sf::Music m_bgmusic;

    bool m_paused = false;

    sf::Clock m_gameClock;
    sf::Clock m_pauseClock;
    sf::Time m_totalPausedTime;

friend void draw(Renderer &ren, const Game &sh);
};

void draw(Renderer &ren, const Game &ga);

#endif // GAME_H
