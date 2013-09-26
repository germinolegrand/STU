#ifndef MENU_H
#define MENU_H

#include "using.h"
#include "TextureManager.h"

class Menu
{
public:
    Menu() = default;
    Menu(TextureManager textures, std::initializer_list<std::pair<sf::String, std::function<void()>>>&& entries);

    void highlightNextEntry();
    void highlightPrevEntry();

    void selectEntry();

private:
    TextureManager m_textures;

    sf::Font m_font;
    std::vector<std::pair<sf::String, std::function<void()>>> m_entries;

    unsigned int m_hilightedEntry = 0;

    friend void draw(Renderer &ren, const Menu& m);
};

#endif // MENU_H
