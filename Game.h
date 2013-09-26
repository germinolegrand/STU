#ifndef GAME_H
#define GAME_H

#include "using.h"
#include <SFML/Audio.hpp>

#include "Menu.h"
#include "Level.h"

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

    void addLevel(std::function<void(Level&)> lvl);
    void loadLevel(unsigned int level);

    enum class State {Quit, Menu, Running, Paused, PlayerLose, PlayerWin};
    State getState() const;

    void frame();

private:
    State m_state = State::Menu;

    Menu m_menu,
         m_pause_menu;

    Menu* m_current_menu = &m_menu;

    std::vector<std::function<void(Level&)>> m_levels;
    std::unique_ptr<Level> m_current_level;

    BulletManager m_ally_bullets,
                  m_ennemy_bullets;

    Hero m_firstHeroEver;
    HeroController m_heroController;
    bool m_heroBulletSpawning = false;
    sf::Time m_heroBulletSpawningInterval = sf::milliseconds(50);

    MonsterManager m_monsters;

    Background m_bg;

    sf::Music m_bgmusic;

    sf::RenderTexture m_pause_rt;

    bool m_paused = true;

    sf::Clock m_gameClock;
    sf::Clock m_pauseClock;
    sf::Time m_totalPausedTime;

    sf::Time getClock() const;

    sf::Time m_animation_prev_clock = getClock();

    void pause(bool pauseOn);
    bool pauseSwitch();

    void heroBulletSpawning(bool activate);
    void slowDown(bool activate);

friend class Level;
friend class GameInputEventProcessor;

friend void draw(Renderer &ren, const Game &sh);
};

#endif // GAME_H
