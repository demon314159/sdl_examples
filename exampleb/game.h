//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

#include "lamp.h"
#include "queue.h"

class Game
{
public:
    Game(int credit, int max_players, int max_balls, Lamp* lamp, Queue* queue);
    ~Game();

    void add_credit();
    void add_player();
    void next_player();

private:
    int m_credit;
    int m_max_players;
    int m_max_balls;
    Lamp* m_lamp;
    Queue* m_queue;
    int m_players;
    int m_player_up;
};

#endif // _GAME_H_
