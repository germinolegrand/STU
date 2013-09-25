#ifndef GAME_H
#define GAME_H

#include "using.h"
#include <SFML/Audio.hpp>

#include "BulletManager.h"

#include "Hero.h"
#include "HeroController.h"

#include "MonsterManager.h"

#include "Background.h"

#include "Level.h"

class TextureManager;

class Game
{
public:
    Game(TextureManager& textures);

    void pause(bool pauseOn);
    bool pauseSwitch();

    void heroBulletSpawning(bool activate);
    void slowDown(bool activate);

    enum class State {Running, PlayerLose, PlayerWin};
    State getState();

    void frame();

private:
    std::multimap<sf::Time, std::function<void()>> m_triggers;

    void executeTriggers();
    void addSimpleTrigger(sf::Time timelaps, std::function<void()> f);
    void addCyclicTrigger(sf::Time interval, std::function<void()> f);

    BulletManager m_ally_bullets,
                  m_ennemy_bullets;

    Hero m_firstHeroEver;
    HeroController m_heroController;
    bool m_heroBulletSpawning = false;
    sf::Time m_heroBulletSpawningInterval = sf::milliseconds(50);

    MonsterManager m_monsters;

    Background m_bg;

    sf::Music m_bgmusic;

    bool m_paused = false;

    sf::Clock m_gameClock;
    sf::Clock m_pauseClock;
    sf::Time m_totalPausedTime;

    sf::Time getClock() const;

    sf::Time m_animation_prev_clock = getClock();

friend void draw(Renderer &ren, const Game &sh);
};

#endif // GAME_H
