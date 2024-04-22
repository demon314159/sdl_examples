//
// scoreboard.cpp
//

#include "scoreboard.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "backglass_guide.h"

#include <stdio.h>

#define SCORE_DELAY  0.15

Scoreboard::Scoreboard(int max_players, int digits,
                       const Float3& position, const Float2& size,
                       const Float2& backglass_image_size,
                       const Float2& trim, const PaintCan& trim_color,
                       float texture_id_backglass, float texture_id_score)
    : m_max_players(max_players)
    , m_digits(digits)
    , m_position(position)
    , m_size(size)
    , m_backglass_image_size(backglass_image_size)
    , m_trim(trim)
    , m_trim_color(trim_color)
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

Scoreboard::~Scoreboard()
{
    delete [] m_data;
    delete [] m_digit;
    delete m_queue;
}

void Scoreboard::clear()
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        m_digit[i] = 0;
    }
}

void Scoreboard::advance(float seconds)
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

bool Scoreboard::non_zero_digits() const
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        if (m_digit[i] != 0) {
            return true;
        }
    }
    return false;
}

void Scoreboard::command_clear_digits(int solenoid_id)
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

void Scoreboard::command_increment_digit(int digit, int solenoid_id)
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

void Scoreboard::command_out_hole(int solenoid_id)
{
    m_solenoid_id = solenoid_id;
}

void Scoreboard::perform_action(int command, int digit, int solenoid_id)
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

int Scoreboard::digits() const
{
    return m_max_players * m_digits;
}

float* Scoreboard::data() const
{
    for (int i = 0; i < (m_max_players * m_digits); i++) {
        m_data[i] = 0.1 * (float) m_digit[i];
    }
    return m_data;
}

void Scoreboard::add_tens(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 2, solenoid_id, SCORE_DELAY);
        }
    }
}

void Scoreboard::add_hundreds(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 3, solenoid_id, SCORE_DELAY);
        }
    }
}

void Scoreboard::add_thousands(int player, int n, int solenoid_id)
{
    for (int i = 0; i < n; i++) {
        if (!m_queue->full()) {
            m_queue->add_action(QCOMMAND_INCREMENT_DIGIT, m_digits * player + m_digits - 4, solenoid_id, SCORE_DELAY);
        }
    }
}

void Scoreboard::start_replay(int sound_solenoid_id, int out_hole_solenoid_id)
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

int Scoreboard::solenoid_id() const
{
    return m_solenoid_id;
}

CadModel Scoreboard::player_digits_model(int player, const Float2& position, const Float2& size, float animation_id_first_digit) const
{
    BackglassGuide bg(m_position, m_size, m_backglass_image_size);
    Float3 fpos = bg.position(position);
    Float2 fsize = bg.size(size);
    CadModel mm;
    for (int i = 0; i < m_digits; i++) {
        float h = fsize.v2 * 0.9;
        float w = h * (0.40 / 0.69);
        CadModel single(PlaneShape(w, h, m_texture_id_score, {0.0, 0.0}, {0.1, 1.0}), PaintCan(0.0, 0.0, 0.0), animation_id_first_digit + (float) (i + (player - 1) * m_digits));
        single.rotate_ax(90.0);
        float gap = (i < (m_digits / 2)) ? -w / 4.0 : w / 4.0;
        mm.add(single, fpos.v1 - w * (float) m_digits / 2.0f + w * (float) i + w / 2.0 + gap, fpos.v2, fpos.v3 + 0.002);
    }
    return mm;
}

CadModel Scoreboard::model(float animation_id_first_digit, float animation_id_scoreboard) const
{
    CadModel mm;
    CadModel backglass(PlaneShape(m_size.v1, m_size.v2, m_texture_id_backglass), PaintCan(1.0, 1.0, 1.0), animation_id_scoreboard);
    mm.add(backglass);
    CadModel barrier1(CubeShape(m_trim.v1, m_trim.v2, m_size.v2 + 2.0 * m_trim.v1), m_trim_color, animation_id_scoreboard);
    CadModel barrier2(CubeShape(m_size.v1 + 2.0 * m_trim.v1, m_trim.v2, m_trim.v1), m_trim_color, animation_id_scoreboard);
    mm.add(barrier1, -m_size.v1 / 2.0 - m_trim.v1 / 2.0, -m_trim.v2 / 2.0f, 0.0);
    mm.add(barrier1, m_size.v1 / 2.0 + m_trim.v1 / 2.0, -m_trim.v2 / 2.0f, 0.0);
    mm.add(barrier2, 0.0, -m_trim.v2 / 2.0, -m_size.v2 / 2.0 - m_trim.v1 / 2.0);
    mm.add(barrier2, 0.0, -m_trim.v2 / 2.0, m_size.v2 / 2.0 + m_trim.v1 / 2.0);
    CadModel under_panel(PlaneShape(m_size.v1 + 2.0 * m_trim.v1, m_size.v2 + 2.0 * m_trim.v1), m_trim_color, animation_id_scoreboard);
    under_panel.rotate_ax(180.0);
    mm.add(under_panel,0.0, -m_trim.v2 + 0.002, 0.0);
    mm.rotate_ax(90.0);
    mm.translate(m_position.v1 + m_size.v1 / 2.0, m_position.v2, m_position.v3);
    mm.add(player_digits_model(1, {0.058, 0.04575}, {0.082, 0.0195}, animation_id_first_digit));
    mm .add(player_digits_model(2, {0.2805, 0.04425}, {0.082, 0.0195}, animation_id_first_digit));
    mm .add(player_digits_model(3, {0.057, 0.2005}, {0.083, 0.018}, animation_id_first_digit));
    mm .add(player_digits_model(4, {0.27925, 0.198}, {0.0835, 0.018}, animation_id_first_digit));
    return mm;
}

