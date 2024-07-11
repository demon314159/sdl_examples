//
// toy.h
//

#ifndef _TOY_H_
#define _TOY_H_

#include "animated_toy.h"
#include "scoreboard_camera.h"
#include "lamp.h"
#include "target.h"
#include "sensor.h"
#include "sound.h"
#include "scoreboard.h"
#include "score.h"
#include "ball.h"
#include "flipper.h"
#include "gauge.h"
#include "table.h"
#include "queue.h"
#include "execute.h"
#include "game.h"
#include "replay_score.h"
#include "light_show.h"
#include <SDL_scancode.h>

class Toy: public AnimatedToy
{
public:
    Toy();
    ~Toy();

    void resize(int w, int h) override;
    void initialize() override;
    bool button(int code, bool shifted, bool on) override;
    bool mouse(SDL_Event* e, bool on) override;
    void advance(int nanoseconds) override;

private:
    ScoreboardCamera* m_scoreboard_camera;
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
    Queue* m_fast_queue;
    Game* m_game;
    Execute* m_execute;
    Table* m_table;
    Flipper* m_left_flipper;
    Flipper* m_right_flipper;
    Flipper* m_top_flipper;
    Gauge* m_gauge;
    ReplayScore* m_replay_score;
    LightShow* m_light_show;

    bool m_last_launch_action_button;
    void build_model();
    void build_uniform();
    void update_uniform();

    void activate_solenoid(int solenoid_id);
    void eject_from_out_hole();
};

#endif // _TOY_H_
