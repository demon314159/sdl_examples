//
// game.h
//

#ifndef _GAME_H_
#define _GAME_H_

#include "sensor.h"
#include "target.h"
#include "lamp.h"
#include "queue.h"
#include "score.h"
#include "replay_score.h"

class Game
{
public:
    Game(int credit, int max_players, int max_balls,
         Sensor* sensor, Target* target, Lamp* lamp, Queue* queue, Queue* fast_queue, const Score* score, ReplayScore* replay_score);
    ~Game();

    void add_player();
    void next_player();
    int players() const;
    void apply_rules();


private:
    int m_max_players;
    int m_max_balls;
    Sensor* m_sensor;
    Target* m_target;
    Lamp* m_lamp;
    Queue* m_queue;
    Queue* m_fast_queue;
    const Score* m_score;
    ReplayScore* m_replay_score;
    int m_players;
    int m_player_up;
    int m_ball_in_play;
    bool m_game_in_progress; // from first score until set_match
    int m_match_value;
    bool m_rollover_a;
    bool m_rollover_b;
    bool m_rollover_c;
    bool m_scored;
    bool m_kings_flag;

    void reset_flags();
    void scoring_sequence();
    void multiscore(int n, int solenoid_id, int score);
    void rollover_rules();
    void target_rules();
    void target_score(int lamp_id);
    bool one_ten_dropped() const;
    bool two_jacks_dropped() const;
    bool jacks_dropped() const;
    bool queens_dropped() const;
    bool kings_dropped() const;
    bool aces_dropped() const;
    void jacks_test();
    void queens_test();
    void kings_test();
    void aces_test();
    void tens_bonus_test();
    void jacks_bonus_test();
    void queens_bonus_test();
    void kings_bonus_test();
    void aces_bonus_test();
};

#endif // _GAME_H_
