//
// light_show.h
//

#ifndef _LIGHT_SHOW_H_
#define _LIGHT_SHOW_H_

#include "lamp.h"

class LightShow
{
public:
    LightShow(float time_step, float delay_after_game, Lamp* lamp);
    ~LightShow();

    void reset();
    void advance(float seconds);

private:
    float m_time_step;
    float m_delay_after_game;
    float m_delay_time;
    float m_time;
    Lamp* m_lamp;
    bool m_running;

    void take_action();
};

#endif // _LIGHT_SHOW_H_
