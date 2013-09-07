#include "Background.h"

Background::Background(TextureManager textures):
    m_textures(textures)
{
    m_repeatSprite1.setTexture(m_textures["rpbg"]);
    m_repeatSprite2.setTexture(m_textures["rpbg"]);
    m_repeatSprite2.setPosition(0, -static_cast<float>(m_textures["rpbg"].getSize().y));
}

Background::~Background()
{
    //dtor
}

void Background::scroll(const sf::Time& clock)
{
    auto timeElapsed = clock - m_scrollClock;

    m_repeatSprite1.move(0, m_scrollSpeed*timeElapsed.asSeconds());
    m_repeatSprite2.move(0, m_scrollSpeed*timeElapsed.asSeconds());

    if(m_repeatSprite1.getPosition().y >= m_textures["rpbg"].getSize().y)
        m_repeatSprite1.move(0, -2.f*static_cast<float>(m_textures["rpbg"].getSize().y));

    if(m_repeatSprite2.getPosition().y >= m_textures["rpbg"].getSize().y)
        m_repeatSprite2.move(0, -2.f*static_cast<float>(m_textures["rpbg"].getSize().y));

    m_scrollClock = clock;
}

void Background::setScrollSpeed(float pixelsPerSec)
{
    m_scrollSpeed = pixelsPerSec;
}


void draw(Renderer &ren, const Background &bg)
{
    draw(ren, bg.m_repeatSprite1);
    draw(ren, bg.m_repeatSprite2);
}
