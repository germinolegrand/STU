#include <iostream>
#include <cstdlib>
#include "Renderer.h"
#include "Game.h"
#include "GameInputEventProcessor.h"

int main()
{
    std::cout << "Hello world!" << std::endl;

    srand(time(0));

    sf::RenderWindow win = {videoMode, "STU", sf::Style::Close, sf::ContextSettings(0,0,8)};

    bool playing = true;
    Game game;

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
