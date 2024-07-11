//
// light_show.cpp
//

#include "light_show.h"

LightShow::LightShow(float time_step, float delay_after_game, Lamp* lamp)
    : m_time_step(time_step)
    , m_delay_after_game(delay_after_game)
    , m_delay_time(0.0)
    , m_time(0.0)
    , m_lamp(lamp)
    , m_running(false)
{
}

LightShow::~LightShow()
{
}

void LightShow::reset()
{
    m_running = false;
    m_time = 0.0;
    m_delay_time = m_delay_after_game;
}

void LightShow::advance(float seconds)
{
    if (m_delay_time > 0.0) {
        m_delay_time -= seconds;
    } else {
        m_time += seconds;
        if (m_time > m_time_step) {
            m_time -= m_time_step;
            take_action();
        }
    }
}

void LightShow::take_action()
{
    m_lamp->toggle(LAMP_ID_5X_BONUS);
}
