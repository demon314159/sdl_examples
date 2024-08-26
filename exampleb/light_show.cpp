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
    , m_sequence_ix(0)
{
}

LightShow::~LightShow()
{
}

void LightShow::reset()
{
    m_time = 0.0;
    m_delay_time = m_delay_after_game;
    m_sequence_ix = 0;
    m_lamp->set(LAMP_ID_SHOOT_AGAIN, false);
}

void LightShow::advance(float seconds)
{
    if (m_delay_time > 0.0) {
        m_delay_time -= seconds;
    } else {
        m_time += seconds;
        if (m_time > m_time_step) {
            m_time -= m_time_step;
            advance_sequence_a();
        }
    }
}

void LightShow::advance_sequence_a()
{
    switch(m_sequence_ix) {
        case 0:
            m_lamp->set(LAMP_ID_SHOOT_AGAIN, false);
            m_lamp->set(LAMP_ID_TENS_BONUS, false);
            m_lamp->set(LAMP_ID_1000_BONUS, false);
            m_lamp->set(LAMP_ID_JACKS_BONUS, false);
            m_lamp->set(LAMP_ID_2000_BONUS, false);
            m_lamp->set(LAMP_ID_QUEENS_BONUS, false);
            m_lamp->set(LAMP_ID_3000_BONUS, false);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, false);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, false);
            m_lamp->set(LAMP_ID_KINGS_BONUS, false);
            m_lamp->set(LAMP_ID_4000_BONUS, false);
            m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, false);
            m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, false);
            m_lamp->set(LAMP_ID_ACES_BONUS, false);
            m_lamp->set(LAMP_ID_5000_BONUS, false);
            m_lamp->set(LAMP_ID_5X_BONUS, false);
            m_lamp->set(LAMP_ID_SPECIAL, false);
            m_lamp->set(LAMP_ID_EXTRA_BALL, false);
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, false);
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, false);
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, false);
            ++m_sequence_ix;
            break;
        case 1:
            m_lamp->set(LAMP_ID_SHOOT_AGAIN, true);
            ++m_sequence_ix;
            break;
        case 2:
            m_lamp->set(LAMP_ID_TENS_BONUS, true);
            m_lamp->set(LAMP_ID_1000_BONUS, true);
            ++m_sequence_ix;
            break;
        case 3:
            m_lamp->set(LAMP_ID_JACKS_BONUS, true);
            m_lamp->set(LAMP_ID_2000_BONUS, true);
            ++m_sequence_ix;
            break;
        case 4:
            m_lamp->set(LAMP_ID_QUEENS_BONUS, true);
            m_lamp->set(LAMP_ID_3000_BONUS, true);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, true);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, true);
            ++m_sequence_ix;
            break;
        case 5:
            m_lamp->set(LAMP_ID_KINGS_BONUS, true);
            m_lamp->set(LAMP_ID_4000_BONUS, true);
            m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, true);
            m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, true);
            ++m_sequence_ix;
            break;
        case 6:
            m_lamp->set(LAMP_ID_ACES_BONUS, true);
            m_lamp->set(LAMP_ID_5000_BONUS, true);
            ++m_sequence_ix;
            break;
        case 7:
            m_lamp->set(LAMP_ID_5X_BONUS, true);
            ++m_sequence_ix;
            break;
        case 8:
            m_lamp->set(LAMP_ID_SPECIAL, true);
            ++m_sequence_ix;
            break;
        case 9:
            m_lamp->set(LAMP_ID_EXTRA_BALL, true);
            ++m_sequence_ix;
            break;
        case 10:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, true);
            ++m_sequence_ix;
            break;
        case 11:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, true);
            ++m_sequence_ix;
            break;
        case 12:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, true);
            ++m_sequence_ix;
            break;
        case 13:
            m_lamp->set(LAMP_ID_SHOOT_AGAIN, false);
            ++m_sequence_ix;
            break;
        case 14:
            m_lamp->set(LAMP_ID_TENS_BONUS, false);
            m_lamp->set(LAMP_ID_1000_BONUS, false);
            ++m_sequence_ix;
            break;
        case 15:
            m_lamp->set(LAMP_ID_JACKS_BONUS, false);
            m_lamp->set(LAMP_ID_2000_BONUS, false);
            ++m_sequence_ix;
            break;
        case 16:
            m_lamp->set(LAMP_ID_QUEENS_BONUS, false);
            m_lamp->set(LAMP_ID_3000_BONUS, false);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_A, false);
            m_lamp->set(LAMP_ID_BOTTOM_ROLLOVER_C, false);
            ++m_sequence_ix;
            break;
        case 17:
            m_lamp->set(LAMP_ID_KINGS_BONUS, false);
            m_lamp->set(LAMP_ID_4000_BONUS, false);
            m_lamp->set(LAMP_ID_BOTTOM_LEFT_ROLLOVER_B, false);
            m_lamp->set(LAMP_ID_BOTTOM_RIGHT_ROLLOVER_B, false);
            ++m_sequence_ix;
            break;
        case 18:
            m_lamp->set(LAMP_ID_ACES_BONUS, false);
            m_lamp->set(LAMP_ID_5000_BONUS, false);
            ++m_sequence_ix;
            break;
        case 19:
            m_lamp->set(LAMP_ID_5X_BONUS, false);
            ++m_sequence_ix;
            break;
        case 20:
            m_lamp->set(LAMP_ID_SPECIAL, false);
            ++m_sequence_ix;
            break;
        case 21:
            m_lamp->set(LAMP_ID_EXTRA_BALL, false);
            ++m_sequence_ix;
            break;
        case 22:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_C, false);
            ++m_sequence_ix;
            break;
        case 23:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_B, false);
            ++m_sequence_ix;
            break;
        case 24:
            m_lamp->set(LAMP_ID_TOP_ROLLOVER_A, false);
            m_sequence_ix = 1;
            break;
        default:
            m_sequence_ix = 0;
            break;
    }
}
