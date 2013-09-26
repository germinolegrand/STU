#include "Level.h"

#include "Game.h"

Level::Level(Game& ga):
    m_ga(ga),
    m_level_time_begin(m_ga.getClock())
{
    //ctor
}

void Level::executeTriggers(sf::Time clock)
{
    m_triggers.erase(begin(m_triggers), find_if(begin(m_triggers), end(m_triggers), [clock](decltype(m_triggers)::value_type& trigger)
    {
        if(trigger.first > clock)
            return true;

        trigger.second();
        return false;
    }));
}

bool Level::isFinished()
{
    return (m_triggers.empty() && distance(begin(m_ga.m_monsters), end(m_ga.m_monsters)) == 0) || isAlive(m_ga.m_firstHeroEver);
}


void Level::addSimpleTrigger(sf::Time timelaps, std::function<void()> f)
{
    m_triggers.insert(decltype(m_triggers)::value_type(m_ga.getClock() + timelaps, f));
}

void Level::addCyclicTrigger(sf::Time interval, std::function<void()> f)
{
    addSimpleTrigger(interval, [this, f, interval]()
    {
        f();
        addCyclicTrigger(interval, f);
    });
}

void Level::spawnMonster(const std::string& type, sf::Vector2f position, std::function<void(sf::Time t, sf::Time prev_t, MonsterControler mc)> animation, int life)
{
    m_ga.m_monsters.spawnMonster(m_ga.getClock(), type, position, animation, life);
}
