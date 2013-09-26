#include <iostream>
#include <cstdlib>
#include <thread>
#include "Renderer.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameInputEventProcessor.h"

int main()
{
    std::cout << "Hello world!" << std::endl;

    srand(time(0));

    sf::RenderWindow win = {videoMode, "STU", sf::Style::Close, sf::ContextSettings(0,0,8)};

    sf::Time prev_show_t;
    sf::Clock showClock;

    TextureManager textureManager("textures/");

    Game game(textureManager);

    game.addLevel([](Level& lvl)
    {
        auto monsterAnimation = [](sf::Time t, sf::Time prev_t, MonsterControler mc)
        {
            mc.move(animation::moveAroundCircle(t, prev_t));

            if(t.asMilliseconds()/1000 > prev_t.asMilliseconds()/1000)
            {
                mc.spawnBullet("ennemy/", animation::goStraight({20.f, 50.f}));
            }
        };

        lvl.spawnMonster("planemonster/", {200, 20}, monsterAnimation, 3);

        lvl.addCyclicTrigger(sf::milliseconds(4000), [&](){ lvl.spawnMonster("planemonster/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });

        lvl.addSimpleTrigger(sf::milliseconds(10000), [&](){ lvl.spawnBossMonster("planemonster/", {350.f, 50.f}, monsterAnimation, 200); });
    });

    GameInputEventProcessor giep(game);

    sf::View gameMainView = win.getDefaultView();

    sf::Event ev;

    while(1)
    {
        while(win.pollEvent(ev))
        {
            if(ev.type == sf::Event::EventType::Closed)
            {
                return 0;
            }
            else if(giep.processInput(ev));
        }

        game.frame();

        if(game.getState() == Game::State::Quit)
        {
            return 0;
        }

        if(showClock.getElapsedTime()/sf::Int64(10000) > prev_show_t/sf::Int64(10000))
        {
            prev_show_t = showClock.getElapsedTime();

            win.clear();

            win.setView(gameMainView);
            draw(win, game);

            win.setView(win.getDefaultView());

            win.display();
        }
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

/**
Perso lock� sur l'�cran
Ennemis qui se d�placent de A � B
ou ennemi immobile int�gr� au d�cors
Vitesse de d�placement du perso : normale et lente (� l'appui d'une touche)
Capacit� de tir affectable et modifiable
tirs ennemis :
- tir droit
- motif
- t�te chercheuse

Boites de dialogue pourles discussion

hitbox perso variable
hitbox ennemie global bound du sprite

des bombes

quand les ennemis meurent ils donnent des points de base + droppent des points

**/

/**
lvl 1 arriv�e du d�sert
lvl 2 arriv�e dans la vile (�lot)
lvl 3 r�seau souterrain
**/
