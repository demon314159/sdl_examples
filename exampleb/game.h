//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

#include "sensor.h"
#include "target.h"
#include "lamp.h"
#include "queue.h"

class Game
{
public:
    Game(int credit, int max_players, int max_balls,
         Sensor* sensor, Target* target, Lamp* lamp, Queue* queue);
    ~Game();

    void add_credit();
    void add_player();
    void next_player();

    void apply_rules();


private:
    int m_credit;
    int m_max_players;
    int m_max_balls;
    Sensor* m_sensor;
    Target* m_target;
    Lamp* m_lamp;
    Queue* m_queue;
    int m_players;
    int m_player_up;
    bool m_game_in_progress; // from first score until set_match

    void scoring_sequence();
    void multiscore(int n, int solenoid_id, int score);
    void rollover_rules();
    void target_rules();
    void target_score(int lamp_id);
    bool jacks_dropped() const;
    bool queens_dropped() const;
    bool kings_dropped() const;
    bool aces_dropped() const;
    void jacks_test();
    void queens_test();
    void kings_test();
    void aces_test();
};

#endif // _GAME_H_
