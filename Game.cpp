#include "Game.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "collision.h"

#include <iostream>
#include <cstdlib>

Game::Game(TextureManager& textures):
    m_ally_bullets(textures.subTextures("bullets/")),
    m_ennemy_bullets(textures.subTextures("bullets/")),
    m_firstHeroEver(textures.subTextures("heroes/")),
    m_monsterManager(textures.subTextures("monsters/")),
    m_bg(textures.subTextures("backgrounds/"))
{
    //m_bgmusic.openFromFile("arabianNight.ogg");//God this is slow !
    //m_bgmusic.play();

    m_firstHeroEver.move({static_cast<float>(videoMode.width)/2, static_cast<float>(videoMode.height)});

    m_monsters.push_back({m_monsterManager["planemonster"]});

    for(int i = 0; i < 100; ++i)
        m_ennemy_bullets.createBullet(getClock(), "ennemy/", {200, 200}, [i](sf::Time t, const sf::Vector2f& v){return v + sf::Vector2f{0.01f*(i+t.asSeconds()), 0.05f*t.asSeconds()};});
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

    auto clock = getClock();

    m_bg.scroll(clock);

    m_ally_bullets.animateBullets(clock);
    m_ennemy_bullets.animateBullets(clock);

    m_heroController.controlHero(clock, m_firstHeroEver);

    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_monsters), end(m_monsters), [](Bullet& b, Monster& m)
    {
        std::cout << "collision between bullets and monster" << std::endl;
    });

    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_ennemy_bullets), end(m_ennemy_bullets), [](Bullet& b1, Bullet& b2)
    {
        std::cout << "collision between bullets" << std::endl;
    });

    std::vector<Bullet*> bullets_to_erase;

    collisions(begin(m_ennemy_bullets), end(m_ennemy_bullets), &m_firstHeroEver, &m_firstHeroEver + 1, [&bullets_to_erase](Bullet& b, Hero& h)
    {
        bullets_to_erase.push_back(&b);
        std::cout << "collision between bullet and hero" << std::endl;
    });

    collisions(begin(m_monsters), end(m_monsters), &m_firstHeroEver, &m_firstHeroEver + 1, [&bullets_to_erase](Monster& m, Hero& h)
    {
        std::cout << "collision between monster and hero" << std::endl;
    });

    for(auto bullet_ptr : bullets_to_erase)
        m_ennemy_bullets.erase(*bullet_ptr);
}

sf::Time Game::getClock() const
{
    return m_gameClock.getElapsedTime() - m_totalPausedTime;
}


void draw(Renderer &ren, const Game& ga)
{
    draw(ren, ga.m_bg);

    for(const auto& monster : ga.m_monsters)
        draw(ren, monster);

    draw(ren, ga.m_firstHeroEver);

    draw(ren, ga.m_ennemy_bullets);
    draw(ren, ga.m_ally_bullets);
}
