#include "HeroCollider.h"

#include "Hero.h"

HeroCollider::HeroCollider(const sf::FloatRect &box): m_box(box)
{
    //ctor
}

HeroCollider::~HeroCollider()
{
    //dtor
}

const sf::Vector2f& HeroCollider::onMove(Hero& he, const sf::Vector2f& pos)
{
    sf::Vector2f newPosition(pos);

    if(pos.x + m_box.left < 0)
        newPosition.x = -m_box.left;
    else if(pos.x + m_box.left + m_box.width > videoMode.width)
        newPosition.x = videoMode.width - m_box.left - m_box.width;

    if(pos.y + m_box.top < 0)
        newPosition.y = -m_box.top;
    else if(pos.y + m_box.top + m_box.height> videoMode.height)
        newPosition.y = videoMode.height - m_box.top - m_box.height;

    return std::move(newPosition);
}

void draw(Renderer& ren, const HeroCollider& coll, const sf::Vector2f& hero_position)
{
    sf::RectangleShape rect({coll.m_box.width, coll.m_box.height});
    rect.setPosition(hero_position + sf::Vector2f{coll.m_box.left, coll.m_box.top});

    rect.setOutlineThickness(1.f);
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Transparent);

    draw(ren, rect);
}

