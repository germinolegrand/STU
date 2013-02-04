#include "Renderer.h"

void draw(Renderer &ren, const sf::Shape &sh)
{
    ren.draw(sh);
}

void draw(Renderer &ren, const sf::Sprite& spr)
{
    ren.draw(spr);
}
