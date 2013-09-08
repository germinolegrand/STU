#include "Game.h"

#include "TextureManager.h"
#include "Renderer.h"

#include <iostream>
#include <cstdlib>

Game::Game(TextureManager& textures):
    m_firstHeroEver(textures.subTextures("heroes/")),
    m_monsterManager(textures.subTextures("monsters/")),
    m_bg(textures.subTextures("backgrounds/"))
{
    //m_bgmusic.openFromFile("arabianNight.ogg");//God this is slow !
    //m_bgmusic.play();

    m_firstHeroEver.move({static_cast<float>(videoMode.width)/2, static_cast<float>(videoMode.height)});

    m_monsters.push_back({m_monsterManager["planemonster"]});
}

Game::~Game()
{
    //dtor
}

void Game::pause(bool pauseOn)
{
    if(m_paused == pauseOn)
        return;

    pauseSwitch();
}

bool Game::pauseSwitch()
{
    m_paused = !m_paused;

    if(m_paused)
    {
        m_pauseClock.restart();
    }
    else
    {
        m_totalPausedTime += m_pauseClock.getElapsedTime();
    }

    std::cout << "pause=" << std::boolalpha << m_paused << std::endl;

    return m_paused;
}

void Game::frame()
{
    if(m_paused)
        return;

    auto clock = m_gameClock.getElapsedTime() - m_totalPausedTime;

    m_bg.scroll(clock);

    m_heroController.controlHero(clock, m_firstHeroEver);
}

void draw(Renderer &ren, const Game& ga)
{
    draw(ren, ga.m_bg);
    draw(ren, ga.m_firstHeroEver);

    for(const auto& monster : ga.m_monsters)
        draw(ren, monster);
}
