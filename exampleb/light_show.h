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
    bool m_reset_flag;
    float m_time_step;
    float m_delay_after_game;
    float m_delay_time;
    float m_time;
    Lamp* m_lamp;
    int m_sequence_ix;

    void advance_sequence_a();
};

#endif // _LIGHT_SHOW_H_
