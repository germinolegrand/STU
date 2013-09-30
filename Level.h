#ifndef LEVEL_H
#define LEVEL_H

#include "using.h"

#include "MonsterControler.h"

class Game;

class Level
{
public:
    Level(Game& ga);

    void executeTriggers(sf::Time clock);

    bool isFinished();

    void addSimpleTrigger(sf::Time timelaps, std::function<void()> f);
    void addCyclicTrigger(sf::Time interval, std::function<void()> f);
    void clearTriggers();

    void spawnMonster(const std::string& type, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life, std::function<void()> onDeath = nullptr);
    void spawnBossMonster(const std::string& type, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life, std::function<void()> onDeath = nullptr);
    void clearMonsters();

private:
    Game& m_ga;

    std::multimap<sf::Time, std::function<void()>> m_triggers;
    sf::Time m_level_time_begin;
};

#endif // LEVEL_H
