//
// score.cpp
//

#include "score.h"
#include "plane_shape.h"

#include <stdio.h>

#define SCORE_DELAY  0.15

Score::Score(int max_players, int digits, const Float3& position, const Float2& size,
             float texture_id_backglass, float texture_id_score)
    : m_max_players(max_players)
    , m_digits(digits)
    , m_position(position)
    , m_size(size)
    , m_texture_id_backglass(texture_id_backglass)
    , m_texture_id_score(texture_id_score)
    , m_digit(new int[max_players * digits])
    , m_data(new float[max_players * digits])
    , m_delay_time(0.0)
    , m_solenoid_id(0)
    , m_queue(new Queue())
{
    clear();
}

Score::~Score()
{
    delete [] m_data;
    delete [] m_digit;
    delete m_queue;
}

void Score::clear()
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        m_digit[i] = 0;
    }
}

void Score::advance(float seconds)
{
    m_solenoid_id = 0;
    if (m_queue->empty()) {
        m_delay_time = 0.0;
    } else {
        if (m_delay_time == 0.0) {
           perform_action(m_queue->action_command(), m_queue->action_digit(), m_queue->action_solenoid_id());
        }
        m_delay_time += seconds;
        if (m_delay_time > m_queue->action_post_delay()) {
            m_delay_time = 0.0;
            m_queue->next_action();
            while (!m_queue->empty() && m_queue->action_command() == QCOMMAND_CLEAR_DIGITS && non_zero_digits() == 0) {
                m_queue->next_action();
            }
        }
    }
}

bool Score::non_zero_digits() const
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        if (m_digit[i] != 0) {
            return true;
        }
    }
    return false;
}

void Score::command_clear_digits(int solenoid_id)
{
    if (non_zero_digits()) {
        m_solenoid_id = solenoid_id;
        for (int i = 0; i < (m_max_players * m_digits); i++) {
            if (m_digit[i] != 0) {
                bool cy = m_digit[i] == 9;
                m_digit[i] = cy ? 0 : m_digit[i] + 1;
            }
        }
    }
}

void Score::command_increment_digit(int digit, int solenoid_id)
{
    m_solenoid_id = solenoid_id;
    int i = digit;
    bool cy = m_digit[i] == 9;
    m_digit[i] = cy ? 0 : m_digit[i] + 1;
    while (cy && i > 0) {
        --i;
        cy = m_digit[i] == 9;
        m_digit[i] = cy ? 0 : m_digit[i] + 1;
    }
    // Carry may extend into LSB of previous player and will stop there because it is zero
    // Force all of the players LSB to zero all of the time to undo this
    for (int i = (m_digits - 1); i < (m_max_players * m_digits); i += m_digits) {
        m_digit[i] = 0;
    }
}

void Score::command_out_hole(int solenoid_id)
{
    m_solenoid_id = solenoid_id;
}

void Score::perform_action(int command, int digit, int solenoid_id)
{
    m_solenoid_id = 0;
    if (command == QCOMMAND_CLEAR_DIGITS) {
        command_clear_digits(solenoid_id);
    } else if (command == QCOMMAND_INCREMENT_DIGIT) {
        command_increment_digit(digit, solenoid_id);
    } else if (command == QCOMMAND_OUT_HOLE) {
        command_out_hole(solenoid_id);
    }
}

int Score::digits() const
{
    return m_max_players * m_digits;
}

float* Score::data() const
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        m_data[i] = 0.1 * (float) m_digit[i];
    }
    return m_data;
}

void Score::add_tens(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 2, solenoid_id, SCORE_DELAY);
        }
    }
}

void Score::add_hundreds(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 3, solenoid_id, SCORE_DELAY);
        }
    }
}

void Score::add_thousands(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 4, solenoid_id, SCORE_DELAY);
        }
    }
}

void Score::start_replay(int sound_solenoid_id, int out_hole_solenoid_id)
{
    int nz_count = 0;
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        if (m_digit[i] != 0) {
            ++nz_count;
        }
    }
    if (nz_count > 0) {
        for (int i = 0; i < 10; i++) {
            m_queue->add_action(QCOMMAND_CLEAR_DIGITS, 0, sound_solenoid_id, SCORE_DELAY);
        }
    }
    m_queue->add_action(QCOMMAND_OUT_HOLE, 0, out_hole_solenoid_id, SCORE_DELAY);
}

int Score::solenoid_id() const
{
    return m_solenoid_id;
}

CadModel Score::model(float animation_id) const
{
//    float k = 0.8;
//    float w = 0.040 * k;
//    float h = 0.069 * k;
    CadModel mm;
//    for (int j = 0; j < m_max_players; j++) {
//        for (int i = 0; i < m_digits; i++) {
//            CadModel score(PlaneShape(w, h, m_texture_id, {0.0, 0.0}, {0.1, 1.0}), PaintCan(1.0, 1.0, 1.0), animation_id + (float) i + (float) (j * m_digits));
//            mm.add(score, w * (float) i, 0.020, h * 1.2 *(float) j);
//        }
//    }

    CadModel backglass(PlaneShape(m_size.v1, m_size.v2, m_texture_id_backglass), PaintCan(1.0, 1.0, 1.0), 0.0);
    mm.add(backglass);
    mm.rotate_ax(40.0);
    mm.translate(m_position.v1 + m_size.v1 / 2.0, m_position.v2, m_position.v3 - m_size.v2 / 2.0);
    return mm;
}

