#ifndef GAME_H
#define GAME_H

#include "using.h"
#include <SFML/Audio.hpp>

#include "BulletManager.h"

#include "Hero.h"
#include "HeroController.h"

#include "MonsterManager.h"

#include "Background.h"

class TextureManager;

class Game
{
public:
    Game(TextureManager& textures);

    void pause(bool pauseOn);
    bool pauseSwitch();

    void frame();

private:
    sf::Time getClock() const;

    BulletManager m_ally_bullets,
                  m_ennemy_bullets;

    Hero m_firstHeroEver;
    HeroController m_heroController;

    MonsterManager m_monsterManager;
    std::vector<Monster> m_monsters;

    Background m_bg;

    sf::Music m_bgmusic;

    bool m_paused = false;

    sf::Clock m_gameClock;
    sf::Clock m_pauseClock;
    sf::Time m_totalPausedTime;

friend class GameInputEventProcessor;

friend void draw(Renderer &ren, const Game &sh);
};

#endif // GAME_H
