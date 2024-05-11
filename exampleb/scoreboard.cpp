//
// scoreboard.cpp
//

#include "scoreboard.h"
#include "plane_shape.h"
#include "cube_shape.h"
#include "backglass_guide.h"

#define MAX_PLAYERS 4
#define PLAYER_DIGITS 6
#define CREDITS_DIGITS 2
#define BALL_IN_PLAY_DIGITS 2

#define TOTAL_DIGITS (MAX_PLAYERS * PLAYER_DIGITS + CREDITS_DIGITS + BALL_IN_PLAY_DIGITS)

#define FLASH_ON_TIME  0.4
#define FLASH_OFF_TIME 0.4

Scoreboard::Scoreboard(const Float3& position, const Float2& size,
                       const Float2& backglass_image_size,
                       const Float2& trim, const PaintCan& trim_color,
                       float texture_id_backglass, float texture_id_score)
    : m_flash_template(true)
    , m_flash_timer(0.0)
    , m_position(position)
    , m_size(size)
    , m_backglass_image_size(backglass_image_size)
    , m_trim(trim)
    , m_trim_color(trim_color)
    , m_texture_id_backglass(texture_id_backglass)
    , m_texture_id_score(texture_id_score)
    , m_digit(new Digit[TOTAL_DIGITS])
    , m_data(new float[TOTAL_DIGITS])
{
}

Scoreboard::~Scoreboard()
{
    delete [] m_data;
    delete [] m_digit;
}

void Scoreboard::advance(float seconds)
{
    m_flash_timer -= seconds;
    if (m_flash_timer <= 0.0) {
        if (m_flash_template) {
            m_flash_template = false;
            m_flash_timer += FLASH_OFF_TIME;
        } else {
            m_flash_template = true;
            m_flash_timer += FLASH_ON_TIME;
        }
    }
}

int Scoreboard::digits() const
{
    return TOTAL_DIGITS;
}

float* Scoreboard::data() const
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        if (m_digit[i].blank) {
            m_data[i] = (1.0f / 11.0f) * (float) 10;
        } else if (m_digit[i].flash) {
            m_data[i] = (1.0f / 11.0f) * (float) (m_flash_template ? m_digit[i].value : 10);
        } else {
            m_data[i] = (1.0f / 11.0f) * (float) m_digit[i].value;
        }
    }
    return m_data;
}

CadModel Scoreboard::player_digits_model(int player, const Float2& position, const Float2& size, float animation_id_first_digit) const
{
    BackglassGuide bg(m_position, m_size, m_backglass_image_size);
    Float3 fpos = bg.position(position);
    Float2 fsize = bg.size(size);
    CadModel mm;
    for (int i = 0; i < PLAYER_DIGITS; i++) {
        float h = fsize.v2 * 0.9;
        float w = h * (0.40 / 0.69);
        CadModel single(PlaneShape(w, h, m_texture_id_score, {0.0, 0.0}, {1.0f / 11.0f, 1.0}), PaintCan(0.0, 0.0, 0.0), animation_id_first_digit + (float) (i + (player - 1) * PLAYER_DIGITS));
        single.rotate_ax(90.0);
        float gap = (i < (PLAYER_DIGITS / 2)) ? -w / 4.0 : w / 4.0;
        mm.add(single, fpos.v1 - w * (float) PLAYER_DIGITS / 2.0f + w * (float) i + w / 2.0 + gap, fpos.v2, fpos.v3 + 0.002);
    }
    return mm;
}

CadModel Scoreboard::credits_model(const Float2& position, const Float2& size, float animation_id_first_digit) const
{
    BackglassGuide bg(m_position, m_size, m_backglass_image_size);
    Float3 fpos = bg.position(position);
    Float2 fsize = bg.size(size);
    CadModel mm;
    int id_off = MAX_PLAYERS * PLAYER_DIGITS;
    for (int i = 0; i < 2; i++) {
        float h = fsize.v2 * 0.9;
        float w = h * (0.40 / 0.69);
        CadModel single(PlaneShape(w, h, m_texture_id_score, {0.0, 0.0}, {1.0f / 11.0f, 1.0}), PaintCan(0.0, 0.0, 0.0), animation_id_first_digit + (float) (id_off + i));
        single.rotate_ax(90.0);
        mm.add(single, fpos.v1 - w  + w * (float) i + w / 2.0, fpos.v2, fpos.v3 + 0.002);
    }
    return mm;
}

CadModel Scoreboard::ball_in_play_model(const Float2& position, const Float2& size, float animation_id_first_digit) const
{
    BackglassGuide bg(m_position, m_size, m_backglass_image_size);
    Float3 fpos = bg.position(position);
    Float2 fsize = bg.size(size);
    CadModel mm;
    int id_off = MAX_PLAYERS * PLAYER_DIGITS + CREDITS_DIGITS;
    for (int i = 0; i < 2; i++) {
        float h = fsize.v2 * 0.9;
        float w = h * (0.40 / 0.69);
        CadModel single(PlaneShape(w, h, m_texture_id_score, {0.0, 0.0}, {1.0f / 11.0f, 1.0}), PaintCan(0.0, 0.0, 0.0), animation_id_first_digit + (float) (id_off + i));
        single.rotate_ax(90.0);
        mm.add(single, fpos.v1 - w  + w * (float) i + w / 2.0, fpos.v2, fpos.v3 + 0.002);
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
    mm.add(player_digits_model(2, {0.2805, 0.04425}, {0.082, 0.0195}, animation_id_first_digit));
    mm.add(player_digits_model(3, {0.057, 0.2005}, {0.083, 0.018}, animation_id_first_digit));
    mm.add(player_digits_model(4, {0.27925, 0.198}, {0.0835, 0.018}, animation_id_first_digit));
    mm.add(credits_model({0.158125, 0.232125}, {0.01825, 0.01025}, animation_id_first_digit));
    mm.add(ball_in_play_model({0.177625, 0.231875}, {0.01825, 0.01025}, animation_id_first_digit));
    return mm;
}

void Scoreboard::set_digit(int ix, const Digit& digit)
{
    m_digit[ix] = digit;
}

int Scoreboard::max_players() const
{
    return MAX_PLAYERS;
}

int Scoreboard::player_digits() const
{
    return PLAYER_DIGITS;
}
