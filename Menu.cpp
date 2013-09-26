#include "Menu.h"

Menu::Menu(TextureManager textures, std::initializer_list<std::pair<sf::String, std::function<void()>>>&& entries):
    m_textures(textures),
    m_entries(std::move(entries))
{
    m_font.loadFromFile("fonts/cour.ttf");
}

void Menu::highlightNextEntry()
{
    m_hilightedEntry = (m_hilightedEntry + 1)%m_entries.size();
}

void Menu::highlightPrevEntry()
{
    m_hilightedEntry = m_hilightedEntry == 0 ? m_entries.size() : (m_hilightedEntry - 1);
}

void Menu::selectEntry()
{
    m_entries[m_hilightedEntry].second();
}


void draw(Renderer &ren, const Menu& m)
{
    sf::Sprite bg(m.m_textures["bg"]);
    draw(ren, bg);

    for(unsigned int i = 0; i < m.m_entries.size(); ++i)
    {
        sf::Text txt(m.m_entries[i].first, m.m_font, 40);
        txt.setPosition({50.f, i*50.f + 150.f});
        txt.setStyle(sf::Text::Style::Italic);

        if(i == m.m_hilightedEntry)
        {
            txt.setString("> " + txt.getString());
            txt.setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
        }

        draw(ren, txt);
    }
}
