#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "using.h"

#include "TextureManager.h"

class Background
{
public:
    Background(TextureManager textures);
    virtual ~Background();

    void scroll(const sf::Time &clock);

    void setScrollSpeed(float pixelsPerSec);

private:
    TextureManager m_textures;

    sf::Sprite m_repeatSprite1,
               m_repeatSprite2;

    sf::Time m_scrollClock;
    float m_scrollSpeed = 100.f;

friend void draw(Renderer &ren, const Background &bg);
};

void draw(Renderer &ren, const Background &bg);

#endif // BACKGROUND_H
