#include "Game.h"

#include "TextureManager.h"
#include "Renderer.h"
#include "collision.h"
#include "animation.h"

#include <iostream>
#include <cstdlib>
#include <complex>

Game::Game(TextureManager& textures):
    m_textures(textures),
    m_menu(textures.subTextures("menus/main/"),
           {{"Jouer", [this](){
               loadLevel(0);
               m_state = State::Running;
           }},{"Quitter", [this](){
               m_state = State::Quit;
           }}}),
    m_pause_menu(textures.subTextures("menus/pause/"),
           {{"Reprendre la partie", [this](){
               pause(false);
           }},{"Recommencer le niveau", [this](){
               loadLevel(0);
               m_state = State::Running;
           }},{"Revenir au menu principal", [this](){
               m_bgmusic.openFromFile("musics/menu.wav");
               m_bgmusic.play();
               m_current_menu = &m_menu;
               m_state = State::Menu;
           }},{"Quitter", [this](){
               m_state = State::Quit;
           }}}),
    m_win_menu(textures.subTextures("menus/win/"),
           {{"Niveau suivant", [this](){
               if(m_current_level_id + 1 < m_levels.size())
               {
                   loadLevel(m_current_level_id + 1);
                   m_state = State::Running;
               }
           }},{"Revenir au menu principal", [this](){
               m_bgmusic.openFromFile("musics/menu.wav");
               m_bgmusic.play();
               m_current_menu = &m_menu;
               m_state = State::Menu;
           }},{"Quitter", [this](){
               m_state = State::Quit;
           }}}),
    m_lose_menu(textures.subTextures("menus/lose/"),
           {{"Recommencer le niveau", [this](){
               loadLevel(0);
               m_state = State::Running;
           }},{"Revenir au menu principal", [this](){
               m_bgmusic.openFromFile("musics/menu.wav");
               m_bgmusic.play();
               m_current_menu = &m_menu;
               m_state = State::Menu;
           }},{"Quitter", [this](){
               m_state = State::Quit;
           }}}),
    m_ally_bullets(textures.subTextures("bullets/")),
    m_ennemy_bullets(textures.subTextures("bullets/")),
    m_firstHeroEver(textures.subTextures("heroes/")),
    m_monsters(textures.subTextures("monsters/")),
    m_bg(textures.subTextures("backgrounds/"))
{
    m_pause_rt.create(videoMode.width, videoMode.height);

    m_bgmusic.setLoop(true);

    m_bgmusic.openFromFile("musics/menu.wav");
    m_bgmusic.play();
}

void Game::addLevel(std::function<void(Level&)> lvl)
{
    m_levels.push_back(std::move(lvl));
}

void Game::loadLevel(unsigned int level)
{
    m_current_level_id = level;

    m_ally_bullets.clearBullets();
    m_ennemy_bullets.clearBullets();
    m_monsters.clearMonsters();

    m_firstHeroEver.~Hero();
    new (&m_firstHeroEver) Hero(m_textures.subTextures("heroes/"));
    m_firstHeroEver.setPosition({static_cast<float>(videoMode.width)/2, static_cast<float>(videoMode.height)});

    m_current_level.reset(new Level(*this));
    m_levels[m_current_level_id](*m_current_level);

    m_bgmusic.openFromFile("musics/theme.wav");
    m_bgmusic.play();

    m_current_menu = &m_pause_menu;

    pause(false);
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

        m_pause_rt.clear(sf::Color(0,0,0,0));
        draw(m_pause_rt, *this);
        m_pause_rt.display();

        m_bgmusic.stop();

        m_state = State::Paused;
    }
    else
    {
        m_totalPausedTime += m_pauseClock.getElapsedTime();

        m_bgmusic.openFromFile("musics/theme.wav");
        m_bgmusic.play();

        m_state = State::Running;
    }

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

Game::State Game::getState() const
{
    return m_state;
}


void Game::frame()
{
    if(m_state == State::Running && m_current_level->isFinished())
    {
        pause(true);
        pause(false);

        if(isAlive(m_firstHeroEver))
        {
            m_current_menu = &m_win_menu;
            m_bgmusic.openFromFile("musics/menu.wav");
            m_state = State::PlayerWin;
        }
        else
        {
            m_current_menu = &m_lose_menu;
            m_bgmusic.openFromFile("musics/menu.wav");
            m_state = State::PlayerLose;
        }
    }

    if(m_state != State::Running)
        return;

    auto clock = getClock();

    m_current_level->executeTriggers(clock);

    m_bg.scroll(clock, m_animation_prev_clock);

    m_monsters.animateMonsters(clock, m_animation_prev_clock, m_ennemy_bullets);

    m_ally_bullets.animateBullets(clock, m_animation_prev_clock);
    m_ennemy_bullets.animateBullets(clock, m_animation_prev_clock);

    m_heroController.controlHero(clock, m_animation_prev_clock, m_firstHeroEver);

    if(m_heroBulletSpawning && clock/m_heroBulletSpawningInterval.asMicroseconds() > m_animation_prev_clock/m_heroBulletSpawningInterval.asMicroseconds())
    {
        m_ally_bullets.spawnBullet(clock, "ally/", getBulletCreationPoint(m_firstHeroEver), animation::goStraight({0.f, -1000.f}));
    }


    std::set<Bullet*> ally_bullets_to_erase,
                         ennemy_bullets_to_erase;

    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_monsters), end(m_monsters), [&ally_bullets_to_erase](Bullet& b, Monster& m)
    {
        takeDamages(m, getDamages(b));
        ally_bullets_to_erase.insert(&b);
    });

//    collisions(begin(m_ally_bullets), end(m_ally_bullets), begin(m_ennemy_bullets), end(m_ennemy_bullets), [](Bullet& b1, Bullet& b2)
//    {
//        std::cout << "collision between bullets" << std::endl;
//    });

    collisions(begin(m_ennemy_bullets), end(m_ennemy_bullets), &m_firstHeroEver, &m_firstHeroEver + 1, [&ennemy_bullets_to_erase](Bullet& b, Hero& h)
    {
        takeDamages(h, getDamages(b));
        ennemy_bullets_to_erase.insert(&b);
    });

    collisions(begin(m_monsters), end(m_monsters), &m_firstHeroEver, &m_firstHeroEver + 1, [](Monster& m, Hero& h)
    {
        takeDamages(h, getDamages(m));
    });


    for(auto bullet_ptr : ally_bullets_to_erase)
        m_ally_bullets.erase(*bullet_ptr);

    for(auto bullet_ptr : ennemy_bullets_to_erase)
        m_ennemy_bullets.erase(*bullet_ptr);

    m_animation_prev_clock = clock;
}


sf::Time Game::getClock() const
{
    return m_gameClock.getElapsedTime() - m_totalPausedTime;
}


void draw(Renderer &ren, const Game& ga)
{
    if(ga.m_state == Game::State::Paused)
    {
        sf::Sprite rt_sprite(ga.m_pause_rt.getTexture());
        rt_sprite.setColor(sf::Color(255,255,255,128));
        draw(ren, rt_sprite);
        draw(ren, ga.m_pause_menu);
        return;
    }

    if(ga.m_state == Game::State::PlayerWin)
    {
        sf::Sprite rt_sprite(ga.m_pause_rt.getTexture());
        rt_sprite.setColor(sf::Color(128,255,128,128));
        draw(ren, rt_sprite);
        draw(ren, ga.m_win_menu);
        return;
    }

    if(ga.m_state == Game::State::PlayerLose)
    {
        sf::Sprite rt_sprite(ga.m_pause_rt.getTexture());
        rt_sprite.setColor(sf::Color(255,16,16,128));
        draw(ren, rt_sprite);
        draw(ren, ga.m_lose_menu);
        return;
    }

    if(ga.m_state == Game::State::Menu)
    {
        sf::Sprite rt_sprite(ga.m_pause_rt.getTexture());
        rt_sprite.setColor(sf::Color(255,255,255,128));
        draw(ren, rt_sprite);
        draw(ren, ga.m_menu);
        return;
    }

    draw(ren, ga.m_bg);

    draw(ren, ga.m_monsters);

    draw(ren, ga.m_firstHeroEver);

    draw(ren, ga.m_ennemy_bullets);
    draw(ren, ga.m_ally_bullets);
}
