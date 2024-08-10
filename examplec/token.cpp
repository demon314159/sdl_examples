//
// token.cpp
//

#include "token.h"
#include "paint_can.h"
#include "tile_shape.h"
#include "tile_border_shape.h"

Token::Token()
    : m_position({0.0, 0.0, 0.0})
    , m_angle({0.0, 0.0, 0.0})
    , m_velocity({0.0, 0.0, 0.0})
    , m_angular_velocity({0.0, 0.0, 0.0})
    , m_time_left(0.0)
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
    float pitch = TILE_PITCH;
    float width = TILE_WIDTH;
    float height = TILE_HEIGHT;
    float thick = TILE_THICK;
    float border = TILE_BORDER;

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
    CadModel t1(TileShape(pitch, width, thick, border, upper, lower, left, right, upper_left, upper_right, lower_left, lower_right), TILE_BODY_COLOR, animation_id);
    CadModel t2(TileBorderShape(pitch, width, height, border, upper, lower, left, right), TILE_BORDER_COLOR, animation_id);
    cm.add(t1, pitch * (float) posh(tile, 0), 0.0, -pitch * (float) posv(tile, 0));
    cm.add(t2, pitch * (float) posh(tile, 0), 0.0, -pitch * (float) posv(tile, 0));
}

void Token::advance(float seconds)
{
    if (m_time_left > seconds) {
        m_time_left -= seconds;
    } else {
        m_time_left = 0.0;
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

Float3 Token::angles(int orientation) const
{
    switch(orientation) {
        case 0: return  {0.0, 0.0, 0.0};
                break;
        case 1: return {0.0, 270.0, 0.0};
                break;
        case 2: return {0.0, 180.0, 0.0};
                break;
        case 3: return {0.0, 90.0, 0.0};
                break;
        case 4: return {0.0, 0.0, 180.0};
                break;
        case 5: return {180.0, 90.0, 0.0};
                break;
        case 6: return {0.0, 180.0, 180.0};
                break;
        case 7: return {180.0, 270.0, 0.0};
                break;
        default: return {0.0, 0.0, 0.0};
    }
}

const float* Token::data()
{
    m_animation.unity();
    Float3 cp = current_value(m_position, m_velocity, m_time_left);
    Float3 ca = current_value(m_angle, m_angular_velocity, m_time_left);
    m_animation.translate(cp.v1, cp.v2, cp.v3);
    m_animation.rotate_ay(ca.v2);
    m_animation.rotate_ax(ca.v1);
    m_animation.rotate_az(ca.v3);
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

Float3 Token::position() const
{
    return m_position;
}

Float3 Token::velocity(const Float3& p1, const Float3& p0, float period) const
{
    Float3 v;
    v.v1 = (p1.v1 - p0.v1) / period;
    v.v2 = (p1.v2 - p0.v2) / period;
    v.v3 = (p1.v3 - p0.v3) / period;
    return v;
}

float Token::angle_diff(float a1, float a0) const
{
    float diff = a1 - a0;
    if (diff > 181.0) {
        diff -= 360.0;
    } else if (diff < -181.0) {
        diff += 360.0;
    }
    return diff;
}

Float3 Token::angular_velocity(const Float3& p1, const Float3& p0, float period) const
{
    Float3 v;

    v.v1 = angle_diff(p1.v1, p0.v1) / period;
    v.v2 = angle_diff(p1.v2, p0.v2) / period;
    v.v3 = angle_diff(p1.v3, p0.v3) / period;
    return v;
}

bool Token::set_position(float posx, float posy, float posz, int orientation, float seconds)
{
    if (m_time_left > 0.0) {
        return false;
    }
    if (seconds > 0.0) {
        m_velocity = velocity({posx, posy, posz}, m_position, seconds);
        m_angular_velocity = angular_velocity(angles(orientation), m_angle, seconds);
        if (m_angular_velocity.v2 != 0.0 && (m_angular_velocity.v1 != 0.0 || m_angular_velocity.v3 != 0.0)) {
            Float3 new_angles = m_angle;
            new_angles.v2 = angles(orientation).v2 - 180.0;
            m_angular_velocity = angular_velocity(new_angles, m_angle, seconds);
        }
        m_time_left = seconds;
    }
    m_position.v1 = posx;
    m_position.v2 = posy;
    m_position.v3 = posz;
    m_angle = angles(orientation);
    return true;
}

Float3 Token::current_value(const Float3& p, const Float3& v, float tleft) const
{
    Float3 cp;
    cp.v1 = p.v1 - tleft * v.v1;
    cp.v2 = p.v2 - tleft * v.v2;
    cp.v3 = p.v3 - tleft * v.v3;
    return cp;
}
