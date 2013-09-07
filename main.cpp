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
