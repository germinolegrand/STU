#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <memory>

#include <SFML/Graphics.hpp>

class TextureManager
{
public:
    TextureManager(std::string path);

    TextureManager subTextures(std::string path);

    sf::Texture& operator[](std::string path);

private:
    std::map<std::string, std::shared_ptr<sf::Texture>> m_textures;

    TextureManager(decltype(m_textures)::iterator begin, decltype(m_textures)::iterator end, std::string path);
};

#endif // TEXTUREMANAGER_H
