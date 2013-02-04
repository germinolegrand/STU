#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

class Game;

class GameInterface
{
public:
    GameInterface(Game &ga);
    virtual ~GameInterface();
protected:
private:
    Game &m_ga;
};

#endif // GAMEINTERFACE_H
