//
// score.cpp
//

#include "score.h"
#include "plane_shape.h"

#define SCORE_DELAY  0.15

Score::Score(float texture_id)
    : m_texture_id(texture_id)
    , m_data(new float[TOTAL_DIGITS])
    , m_delay_time(0.0)
    , m_queue()
    , m_sound(0)
{
    clear();
}

Score::~Score()
{
    delete [] m_data;
}

void Score::clear()
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        m_digit[i] = 0;
    }
}

void Score::advance(float seconds)
{
    m_sound = 0;
    if (m_queue.empty()) {
        m_delay_time = 0.0;
    } else {
        if (m_delay_time == 0.0) {
           perform_action(m_queue.action_digit(), m_queue.action_sound_id());
        }
        m_delay_time += seconds;
        if (m_delay_time > m_queue.action_delay()) {
            m_delay_time = 0.0;
            m_queue.next_action();
        }
    }
}

bool Score::non_zero_digits() const
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        if (m_digit[i] != 0) {
            return true;
        }
    }
    return false;
}

void Score::perform_action(int digit, int sound_id)
{
    if (digit == TOTAL_DIGITS) {
        if (non_zero_digits()) {
            m_sound = sound_id;
            for (int i = 0; i < TOTAL_DIGITS; i++) {
                if (m_digit[i] != 0) {
                    bool cy = m_digit[i] == 9;
                    m_digit[i] = cy ? 0 : m_digit[i] + 1;
                }
            }
        }
    } else {
        m_sound = sound_id;
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
        for (int i = (SCORE_DIGITS - 1); i < TOTAL_DIGITS; i += SCORE_DIGITS) {
            m_digit[i] = 0;
        }
    }
}

int Score::digits() const
{
    return TOTAL_DIGITS;
}

CadModel Score::model(float animation_id) const
{
    float k = 0.8;
    float w = 0.040 * k;
    float h = 0.069 * k;
    CadModel mm;
    for (int j = 0; j < MAX_PLAYERS; j++) {
        for (int i = 0; i < SCORE_DIGITS; i++) {
            CadModel score(PlaneShape(w, h, m_texture_id, {0.0, 0.0}, {0.1, 1.0}), PaintCan(1.0, 1.0, 1.0), animation_id + (float) i + (float) (j * SCORE_DIGITS));
            mm.add(score, w * (float) i, 0.020, h * 1.2 *(float) j);
        }
    }
    mm.rotate_ax(90.0 - 40.0);
    mm.translate(-0.2, 0.05, 0.2);
    return mm;
}

float* Score::data() const
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        m_data[i] = 0.1 * (float) m_digit[i];
    }
    return m_data;
}

void Score::add_tens(int player, int n, int sound_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue.full()) {
            m_queue.add_action(SCORE_DIGITS * player + SCORE_DIGITS - 2, sound_id, SCORE_DELAY);
        }
    }
}

void Score::add_hundreds(int player, int n, int sound_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue.full()) {
            m_queue.add_action(SCORE_DIGITS * player + SCORE_DIGITS - 3, sound_id, SCORE_DELAY);
        }
    }
}

void Score::add_thousands(int player, int n, int sound_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue.full()) {
            m_queue.add_action(SCORE_DIGITS * player + SCORE_DIGITS - 4, sound_id, SCORE_DELAY);
        }
    }
}

void Score::start_replay(int sound_id)
{
    int nz_count = 0;
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        if (m_digit[i] != 0) {
            ++nz_count;
        }
    }
    if (nz_count > 0) {
        for (int i = 0; i < 10; i++) {
            m_queue.add_action(TOTAL_DIGITS, sound_id, SCORE_DELAY);
        }
    }
}

int Score::sound() const
{
    return m_sound;
}
