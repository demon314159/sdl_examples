//
// token.cpp
//

#include "token.h"
#include "paint_can.h"
#include "tile_shape.h"
#include "tile_border_shape.h"

Token::Token()
    : m_position({0.0, 0.0, 0.0})
    , m_angle(0.0)
    , m_velocity({0.0, 0.0, 0.0})
    , m_angular_velocity(0.0)
    , m_translation_time_left(0.0)
    , m_rotation_time_left(0.0)
    , m_tiles(0)
    , m_animation()
{
}

Token::~Token()
{
}

Token& Token::add_tile(int posh, int posv)
{
    if (m_tiles < MAX_TILES) {
        m_tile[m_tiles] = {posh, posv};
        ++m_tiles;
    }
    return *this;
}

int Token::tiles() const
{
    return m_tiles;
}

int Token::posh(int tix, int orientation) const
{
    switch(orientation) {
        case 0: return  m_tile[tix].posh;
                break;
        case 1: return  m_tile[tix].posv;
                break;
        case 2: return -m_tile[tix].posh;
                break;
        case 3: return -m_tile[tix].posv;
                break;
        case 4: return -m_tile[tix].posh;
                break;
        case 5: return  m_tile[tix].posv;
                break;
        case 6: return  m_tile[tix].posh;
                break;
        case 7: return -m_tile[tix].posv;
                break;
        default: return 0;
    }
}

int Token::posv(int tix, int orientation) const
{
    switch(orientation) {
        case 0: return  m_tile[tix].posv;
                break;
        case 1: return -m_tile[tix].posh;
                break;
        case 2: return -m_tile[tix].posv;
                break;
        case 3: return  m_tile[tix].posh;
                break;
        case 4: return  m_tile[tix].posv;
                break;
        case 5: return  m_tile[tix].posh;
                break;
        case 6: return -m_tile[tix].posv;
                break;
        case 7: return -m_tile[tix].posh;
                break;
        default: return 0;
    }
}

void Token::one_tile(CadModel& cm, int tile, float animation_id) const
{
    float pitch = 0.010;
    float width = 0.0095;
    float height = 0.001;
    float thick = 0.0005;
    float border = 0.001;
    PaintCan dark_yellow(0.8, 0.8, 0.0);
    PaintCan yellow(1.0, 1.0, 0.0);

    int base_posh = posh(tile, 0);
    int base_posv = posv(tile, 0);
    bool upper = occupied(base_posh, base_posv + 1);
    bool lower = occupied(base_posh, base_posv - 1);
    bool left = occupied(base_posh - 1, base_posv);
    bool right = occupied(base_posh + 1, base_posv);
    bool upper_left = upper && left && occupied(base_posh - 1, base_posv + 1);
    bool upper_right = upper && right && occupied(base_posh + 1, base_posv + 1);
    bool lower_left = lower && left && occupied(base_posh - 1, base_posv - 1);
    bool lower_right = lower && right && occupied(base_posh + 1, base_posv - 1);
    CadModel t1(TileShape(pitch, width, thick, border, upper, lower, left, right, upper_left, upper_right, lower_left, lower_right), dark_yellow, animation_id);
    CadModel t2(TileBorderShape(pitch, width, height, border, upper, lower, left, right), yellow, animation_id);
    cm.add(t1, pitch * (float) posh(tile, 0), 0.0, -pitch * (float) posv(tile, 0));
    cm.add(t2, pitch * (float) posh(tile, 0), 0.0, -pitch * (float) posv(tile, 0));
}

void Token::advance(float seconds)
{
    if (m_translation_time_left >= seconds) {
        m_translation_time_left -= seconds;
    } else {
        m_translation_time_left = 0.0;
    }
    if (m_rotation_time_left >= seconds) {
        m_rotation_time_left -= seconds;
    } else {
        m_rotation_time_left = 0.0;
    }
}

CadModel Token::model(float animation_id) const
{
    CadModel cm;

    for (int i = 0; i < m_tiles; i++) {
        one_tile(cm, i, animation_id);
    }
    return cm;
}

Float3 Token::current_position() const
{
    Float3 cp;
    cp.v1 = m_position.v1 - m_velocity.v1 * m_translation_time_left;
    cp.v2 = m_position.v2 - m_velocity.v2 * m_translation_time_left;
    cp.v3 = m_position.v3 - m_velocity.v3 * m_translation_time_left;
    return cp;
}

float Token::current_angle() const
{
    float ca;
    ca = m_angle - m_angular_velocity * m_rotation_time_left;
    return ca;
}

const float* Token::data()
{
    m_animation.unity();
    Float3 cp = current_position();
    float ca = current_angle();
    m_animation.translate(cp.v1, cp.v2, cp.v3);
    m_animation.rotate_ay(ca);
    return m_animation.data();
}

bool Token::occupied(int ph, int pv) const
{
    for (int i = 0; i < m_tiles; i++) {
        if (posh(i, 0) == ph && posv(i, 0) == pv) {
            return true;
        }
    }
    return false;
}

void Token::set_position(float posx, float posy, float posz, float seconds)
{
    Float3 cp = current_position();
    if (seconds > 0.0) {
        m_velocity.v1 = (posx - cp.v1) / seconds;
        m_velocity.v2 = (posy - cp.v2) / seconds;
        m_velocity.v3 = (posz - cp.v3) / seconds;
        m_translation_time_left += seconds;
    } else {
        m_translation_time_left = 0.0;
    }
    m_position.v1 = posx;
    m_position.v2 = posy;
    m_position.v3 = posz;
}

void Token::set_angle(float angle, float seconds)
{
    float ca = current_angle();
    if (seconds > 0.0) {
        m_angular_velocity = (angle - ca) / seconds;
        m_rotation_time_left += seconds;
    } else {
        m_rotation_time_left = 0.0;
    }
    m_angle = angle;
}

