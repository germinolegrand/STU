#include "Game.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "collision.h"
#include "animation.h"

#include <iostream>
#include <cstdlib>
#include <complex>

Game::Game(TextureManager& textures):
    m_ally_bullets(textures.subTextures("bullets/")),
    m_ennemy_bullets(textures.subTextures("bullets/")),
    m_firstHeroEver(textures.subTextures("heroes/")),
    m_monsters(textures.subTextures("monsters/")),
    m_bg(textures.subTextures("backgrounds/"))
{
    //m_bgmusic.openFromFile("arabianNight.ogg");//God this is slow !
    //m_bgmusic.play();

    m_firstHeroEver.move({static_cast<float>(videoMode.width)/2, static_cast<float>(videoMode.height)});

    auto monsterAnimation = [](sf::Time t, sf::Time prev_t, MonsterControler mc)
    {
        auto prev_pos = std::polar(50.f, prev_t.asSeconds());
        auto pos = std::polar(50.f, t.asSeconds());
        mc.move({real(pos) - real(prev_pos), imag(pos) - imag(prev_pos)});

        if(t.asMilliseconds()/1000 > prev_t.asMilliseconds()/1000)
        {
            mc.spawnBullet("ennemy/", animation::goStraight({20.f, 200.f}));
        }
    };

    m_monsters.spawnMonster(getClock(), "planemonster/", {200, 20}, monsterAnimation, 3);

    addCyclicTrigger(sf::milliseconds(4000), [&](){ m_monsters.spawnMonster(getClock(), "planemonster/", {static_cast<float>(rand()%600), static_cast<float>(rand()%400)}, monsterAnimation, 3); });
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

void Game::heroBulletSpawning(bool activate)
{
    m_heroBulletSpawning = activate;
}

void Game::slowDown(bool activate)
{
    m_heroController.slowDown(activate);
}

Game::State Game::getState()
{
    return distance(begin(m_monsters), end(m_monsters)) == 0 ? State::PlayerWin
                                                             : isAlive(m_firstHeroEver) ? State::Running
                                                                                        : State::PlayerLose;
}


void Game::frame()
{
    if(m_paused)
        return;

    auto clock = getClock();

    executeTriggers();

    m_bg.scroll(clock, m_animation_prev_clock);

    m_monsters.animateMonsters(clock, m_animation_prev_clock, m_ennemy_bullets);

    m_ally_bullets.animateBullets(clock, m_animation_prev_clock);
    m_ennemy_bullets.animateBullets(clock, m_animation_prev_clock);

    m_heroController.controlHero(clock, m_animation_prev_clock, m_firstHeroEver);

    if(m_heroBulletSpawning && clock/m_heroBulletSpawningInterval.asMicroseconds() > m_animation_prev_clock/m_heroBulletSpawningInterval.asMicroseconds())
    {
        m_ally_bullets.spawnBullet(clock, "ally/", getBulletCreationPoint(m_firstHeroEver), animation::goStraight({0.f, -1000.f}));
    }


    std::vector<Bullet*> ally_bullets_to_erase,
                         ennemy_bullets_to_erase;

    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_monsters), end(m_monsters), [&ally_bullets_to_erase](Bullet& b, Monster& m)
    {
        takeDamages(m, getDamages(b));
        ally_bullets_to_erase.push_back(&b);
        std::cout << "collision between bullets and monster" << std::endl;
    });

    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_ennemy_bullets), end(m_ennemy_bullets), [](Bullet& b1, Bullet& b2)
    {
        std::cout << "collision between bullets" << std::endl;
    });

    collisions(begin(m_ennemy_bullets), end(m_ennemy_bullets), &m_firstHeroEver, &m_firstHeroEver + 1, [&ennemy_bullets_to_erase](Bullet& b, Hero& h)
    {
        takeDamages(h, getDamages(b));
        ennemy_bullets_to_erase.push_back(&b);
        std::cout << "collision between bullet and hero" << std::endl;
    });

    collisions(begin(m_monsters), end(m_monsters), &m_firstHeroEver, &m_firstHeroEver + 1, [](Monster& m, Hero& h)
    {
        takeDamages(h, getDamages(m));
        std::cout << "collision between monster and hero" << std::endl;
    });


    for(auto bullet_ptr : ally_bullets_to_erase)
        m_ally_bullets.erase(*bullet_ptr);

    for(auto bullet_ptr : ennemy_bullets_to_erase)
        m_ennemy_bullets.erase(*bullet_ptr);

    m_animation_prev_clock = clock;
}


void Game::addSimpleTrigger(sf::Time timelaps, std::function<void()> f)
{
    m_triggers.insert(decltype(m_triggers)::value_type(getClock() + timelaps, f));
}

void Game::addCyclicTrigger(sf::Time interval, std::function<void()> f)
{
    addSimpleTrigger(interval, [this, f, interval]()
    {
        f();
        addCyclicTrigger(interval, f);
    });
}

void Game::executeTriggers()
{
    auto clock = getClock();
    m_triggers.erase(begin(m_triggers), find_if(begin(m_triggers), end(m_triggers), [clock](decltype(m_triggers)::value_type& trigger)
    {
        if(trigger.first > clock)
            return true;

        trigger.second();
        return false;
    }));
}

sf::Time Game::getClock() const
{
    return m_gameClock.getElapsedTime() - m_totalPausedTime;
}


void draw(Renderer &ren, const Game& ga)
{
    draw(ren, ga.m_bg);

    draw(ren,ga.m_monsters);

    draw(ren, ga.m_firstHeroEver);

    draw(ren, ga.m_ennemy_bullets);
    draw(ren, ga.m_ally_bullets);
}
