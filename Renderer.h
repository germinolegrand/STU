#ifndef RENDERER_H
#define RENDERER_H

#include "using.h"

const sf::VideoMode videoMode = {800, 600, sf::VideoMode::getDesktopMode().bitsPerPixel};

//template <class T>
//void draw(Renderer &ren, const T&);

void draw(Renderer &ren, const sf::Shape& sh);
void draw(Renderer &ren, const sf::Sprite& spr);

#endif // RENDERER_H
