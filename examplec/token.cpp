//
// token.cpp
//

#include "token.h"
#include "paint_can.h"
#include "tile_shape.h"

Token::Token()
    : m_posx(0.0)
    , m_posy(0.0)
    , m_posz(0.0)
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
    float border = 0.001;
    PaintCan yellow(1.0, 1.0, 0.0);

    int base_posh = posh(tile, 0);
    int base_posv = posv(tile, 0);
    bool upper = occupied(base_posh, base_posv - 1);
    bool lower = occupied(base_posh, base_posv + 1);
    bool left = occupied(base_posh - 1, base_posv);
    bool right = occupied(base_posh + 1, base_posv);
    CadModel t(TileShape(pitch, width, height, border, upper, lower, left, right), yellow, animation_id);
    cm.add(t, pitch * (float) posh(tile, 0), 0.0, pitch * (float) posv(tile, 0));
}

CadModel Token::model(float animation_id) const
{
    CadModel cm;

    for (int i = 0; i < m_tiles; i++) {
        one_tile(cm, i, animation_id);
    }
    return cm;
}

const float* Token::data()
{
    m_animation.unity();
    m_animation.translate(m_posx, 0.0, m_posz);

    // Multipy mm times the rotation matrix
//    m_animation = m_animation * m_orientation.rotation_matrix();
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

void Token::set_position(float posx, float posy, float posz)
{
    m_posx = posx;
    m_posy = posy;
    m_posz = posz;
}
