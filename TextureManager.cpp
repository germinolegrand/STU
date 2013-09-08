#include "TextureManager.h"

#include <iostream>

#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

TextureManager::TextureManager(std::string path)
{
    DIR* current_dir = nullptr;
    if(!(current_dir = opendir(path.c_str())))
       throw std::invalid_argument("invalid path: \"" + path + "\"");

    std::vector<DIR*> dir_arbo{{current_dir}};
    std::string dir_arbo_path;

    while(!dir_arbo.empty())
    {
        dirent* dir_entity = readdir(current_dir);

        if(!dir_entity)
        {
            auto last_dir_pos = dir_arbo_path.substr(0, dir_arbo_path.size() - 1).find_last_of("/");
            dir_arbo_path.resize(last_dir_pos == std::string::npos ? 0 : last_dir_pos);
            dir_arbo.pop_back();
            current_dir = dir_arbo.back();

            continue;
        }

        if(dir_entity->d_name == std::string(".") || dir_entity->d_name == std::string(".."))
        {
            continue;
        }

        std::string dir_entity_path = path + dir_arbo_path + dir_entity->d_name;

        if(DIR* maybe_dir = opendir(dir_entity_path.c_str()))
            //it's a directory
        {
            current_dir = maybe_dir;
            dir_arbo.push_back(current_dir);
            dir_arbo_path += dir_entity->d_name + std::string("/");

            continue;
        }

        auto texture = std::make_shared<sf::Texture>();

        if(texture->loadFromFile(dir_entity_path))
        {
            std::string texture_name(dir_entity->d_name);
            m_textures[dir_arbo_path + texture_name.substr(0, texture_name.find_last_of("."))] = texture;
        }
    }

    for(auto dir : dir_arbo)
        closedir(dir);

    for(auto& texture_pair : m_textures)
        std::cout << texture_pair.first << std::endl;
}

TextureManager::TextureManager(decltype(m_textures)::iterator begin, decltype(m_textures)::iterator end, std::string path)
{
    for_each(begin, end, [&path, this](decltype(m_textures)::value_type& texture_pair){
        m_textures[texture_pair.first.substr(path.size())] = texture_pair.second;
    });

    for(auto& texture_pair : m_textures)
        std::cout << texture_pair.first << std::endl;
}


TextureManager TextureManager::subTextures(std::string path)
{
    auto lower_bound_it = m_textures.lower_bound(path);

    return {lower_bound_it, find_if(lower_bound_it, end(m_textures), [&path](decltype(m_textures)::value_type& texture_pair){
                                return texture_pair.first.substr(0, path.size()) != path;
                            }), path};
}

sf::Texture& TextureManager::operator[](std::string path)
{
    return *m_textures.at(path);
}

