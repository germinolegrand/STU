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



<<<<<<< HEAD
=======
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

        lvl.spawnMonster("GROS-BALOURD/", {200, 20}, monsterAnimation, 3);

        lvl.addCyclicTrigger(sf::milliseconds(4000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });

        lvl.addSimpleTrigger(sf::milliseconds(10000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
    });

>>>>>>> debug final
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

        lvl.spawnMonster("GROS-BALOURD/", {200, 20}, monsterAnimation, 3);

<<<<<<< HEAD
        lvl.addCyclicTrigger(sf::milliseconds(4000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });

        lvl.addSimpleTrigger(sf::milliseconds(10000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
=======
        lvl.addCyclicTrigger(sf::milliseconds(3000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });

        lvl.addSimpleTrigger(sf::milliseconds(7000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
>>>>>>> debug final
    });

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

        lvl.spawnMonster("GROS-BALOURD/", {200, 20}, monsterAnimation, 3);
<<<<<<< HEAD

        lvl.addCyclicTrigger(sf::milliseconds(3000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });

        lvl.addSimpleTrigger(sf::milliseconds(7000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
    });

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

        lvl.spawnMonster("GROS-BALOURD/", {200, 20}, monsterAnimation, 3);
=======
>>>>>>> debug final
        lvl.addCyclicTrigger(sf::milliseconds(3000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });
        lvl.addCyclicTrigger(sf::milliseconds(3000), [&](){ lvl.spawnMonster("GROS-BALOURD/", {static_cast<float>(rand()%800), static_cast<float>(rand()%200)}, monsterAnimation, rand()%100); });
        lvl.addSimpleTrigger(sf::milliseconds(4000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
        lvl.addSimpleTrigger(sf::milliseconds(7000), [&](){ lvl.spawnBossMonster("GIGA-BALOURD/", {350.f, 50.f}, monsterAnimation, 200, [&](){ lvl.clearTriggers(); }); });
    });


    GameInputEventProcessor giep(game);

    sf::View gameMainView = win.getDefaultView();

    sf::Event ev;

    while(1)
    {
        game.frame();

        while(win.pollEvent(ev))
        {
            if(giep.processInput(ev));
        }

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
Perso locké sur l'écran
Ennemis qui se déplacent de A à B
ou ennemi immobile intégré au décors
Vitesse de déplacement du perso : normale et lente (à l'appui d'une touche)
Capacité de tir affectable et modifiable
tirs ennemis :
- tir droit
- motif
- tête chercheuse

Boites de dialogue pourles discussion

hitbox perso variable
hitbox ennemie global bound du sprite

des bombes

quand les ennemis meurent ils donnent des points de base + droppent des points

**/

/**
lvl 1 arrivée du désert
lvl 2 arrivée dans la vile (îlot)
lvl 3 réseau souterrain
**/
