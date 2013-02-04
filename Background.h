#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "using.h"

class Background
{
public:
    Background();
    virtual ~Background();

    void scroll(const sf::Time &clock);

    void setScrollSpeed(float pixelsPerSec);

private:
    sf::Texture m_repetitiveTexture;
    sf::Sprite m_repeatSprite1,
               m_repeatSprite2;

    sf::Time m_scrollClock;
    float m_scrollSpeed = 100.f;

friend void draw(Renderer &ren, const Background &bg);
};

void draw(Renderer &ren, const Background &bg);

#endif // BACKGROUND_H
