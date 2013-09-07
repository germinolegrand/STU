#include <iostream>
#include <cstdlib>
#include "Renderer.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameInputEventProcessor.h"

int main()
{
    std::cout << "Hello world!" << std::endl;

    srand(time(0));

    sf::RenderWindow win = {videoMode, "STU", sf::Style::Close, sf::ContextSettings(0,0,8)};

    TextureManager textureManager("textures/");

    bool playing = true;
    Game game(textureManager);

    GameInputEventProcessor giep(game);

    sf::View gameMainView = win.getDefaultView();

    sf::Event ev;

    while(playing)
    {
        while(win.pollEvent(ev))
        {
            if(ev.type == sf::Event::EventType::Closed)
            {
                playing = false;
            }
            else if(giep.processInput(ev));
        }

        game.frame();

        win.clear();

        win.setView(gameMainView);
        draw(win, game);

        win.setView(win.getDefaultView());

        win.display();
    }

    return 0;
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
