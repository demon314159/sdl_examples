//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "cad_model.h"
#include "matrix4x4.h"
#include "lamp.h"
#include "target.h"
#include "sensor.h"
#include "sound.h"
#include "scoreboard.h"
#include "score.h"
#include "ball.h"
#include "flipper.h"
#include "table.h"
#include "queue.h"
#include "execute.h"

class Toy
{
public:
    #define ANIMATION_0_ID 2.0
    #define ANIMATION_1_ID 3.0
    #define ANIMATION_2_ID 4.0
    #define ANIMATION_3_ID 5.0

    Toy();
    ~Toy();

    void initialize();
    CadModel* get_model() const;
    int animation_matrices() const;
    Matrix4x4 get_animation_matrix(int i) const;

    void left_action_button(bool on);
    void right_action_button(bool on);
    void launch_action_button(bool on);
    void replay_action_button(bool on);

    void advance(int nanoseconds);

    const Lamp* get_lamp() const;
    const Target* get_target() const;
    const Scoreboard* get_scoreboard() const;

private:
    float m_seconds;
    int m_player;
    Ball* m_ball;
    Lamp* m_lamp;
    Target* m_target;
    Sensor* m_sensor;
    Sound* m_sound;
    Scoreboard* m_scoreboard;
    Score* m_score;
    Queue* m_queue;
    Execute* m_execute;
    Table* m_table;
    Flipper* m_left_flipper;
    Flipper* m_right_flipper;
    Flipper* m_top_flipper;
    CadModel* m_model;
    bool m_last_launch_action_button;
    void build_model();
    void apply_rules();
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

    void activate_solenoid(int solenoid_id);
    void eject_from_out_hole();
    void multiscore(int n, int solenoid_id, int score);
};

#endif // _TOY_H_
