//
// token_set.cpp
//
#include "token_set.h"
#include "dock.h"
#include <algorithm>

TokenSet::TokenSet(void)
    : m_tokens(0)
{
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 0).add_tile(1, 1).add_tile(2, 0));    // token_id = 0 == 26a
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(0, 4).add_tile(0, 5));    // token_id = 1
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(0, 4).add_tile(1, 4));    // token_id = 2
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(0, 4).add_tile(1, 3));    // token_id = 3
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(0, 4).add_tile(1, 2));    // token_id = 4
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(1, 1).add_tile(1, 2).add_tile(1, 3).add_tile(2, 3));    // token_id = 5
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(1, 3).add_tile(1, 4));    // token_id = 6
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 3).add_tile(1, 4));    // token_id = 7
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 2).add_tile(1, 3));    // token_id = 8
    add_token(Token().add_tile(0, 0).add_tile(1, 0).add_tile(1, 1).add_tile(1, 2).add_tile(1, 3).add_tile(2, 3));    // token_id = 9
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(-1, 3).add_tile(1, 3));   // token_id = 10
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 3).add_tile(2, 3));    // token_id = 11
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 0).add_tile(1, 1).add_tile(1, 2));    // token_id = 12
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(1, 3).add_tile(2, 3));    // token_id = 13
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(1, 1).add_tile(1, 2).add_tile(2, 2).add_tile(2, 3));    // token_id = 14
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 1).add_tile(1, 2));    // token_id = 15
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(-1, 2).add_tile(1, 2));   // token_id = 16
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 1).add_tile(1, 3));    // token_id = 17
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(1, 3).add_tile(2, 2));    // token_id = 18
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(2, 2).add_tile(2, 3));    // token_id = 19
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 1).add_tile(1, 2).add_tile(1, 3));    // token_id = 20
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(1, 0).add_tile(1, 1).add_tile(2, 1).add_tile(2, 2));    // token_id = 21
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(1, 0).add_tile(1, 1).add_tile(1, 2).add_tile(2, 1));    // token_id = 22
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 0).add_tile(1, 3));    // token_id = 23
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(-1, 1).add_tile(-1, 2).add_tile(1, 1).add_tile(1, 2));  // token_id = 24
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(2, 2).add_tile(2, 1));    // token_id = 25
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 0).add_tile(1, 1).add_tile(2, 0));    // token_id = 26
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(-1, 2).add_tile(1, 3));   // token_id = 27
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 2).add_tile(2, 2));    // token_id = 28
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 0).add_tile(1, 2).add_tile(1, 3));    // token_id = 29
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 1).add_tile(2, 1).add_tile(2, 2));    // token_id = 30
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(-1, 2).add_tile(1, 1).add_tile(1, 2));   // token_id = 31
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(-1, 2).add_tile(1, 2).add_tile(1, 3));   // token_id = 32
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(-1, 1).add_tile(1, 3));   // token_id = 33
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(-1, 1).add_tile(1, 2));   // token_id = 34
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(-1, 1).add_tile(1, 2).add_tile(1, 3));   // token_id = 35
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(1, 2).add_tile(1, 3));    // token_id = 36 == 8a
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(1, 1).add_tile(1, 2).add_tile(2, 2).add_tile(2, 3));    // token_id = 37 == 14a
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(1, 2).add_tile(2, 2).add_tile(2, 1));    // token_id = 38 == 25a
    add_token(Token().add_tile(0, 0).add_tile(0, 1).add_tile(0, 2).add_tile(0, 3).add_tile(0, 4).add_tile(0, 5));    // token_id = 39 == 1a
}

TokenSet::~TokenSet()
{
}

void TokenSet::add_token(const Token& token)
{
    if (m_tokens < MAX_TOKENS) {
        m_token[m_tokens] = token;
        ++m_tokens;
    }
}

int TokenSet::tokens() const
{
    return m_tokens;
}

int TokenSet::tiles(int token_id) const
{
    return m_token[token_id].tiles();
}

int TokenSet::posh(int token_id, int tix, int orientation) const
{
    return m_token[token_id].posh(tix, orientation);
}

int TokenSet::posv(int token_id, int tix, int orientation) const
{
    return m_token[token_id].posv(tix, orientation);
}

bool TokenSet::token_contained(int token_id, int orientation, int ph, int pv, int dimh, int dimv) const
{
    for (int i = 0; i < tiles(token_id); i++) {
        int hpos = ph + posh(token_id, i, orientation);
        if (hpos < 0 || hpos >= dimh)
            return false;
        int vpos = pv + posv(token_id, i, orientation);
        if (vpos < 0 || vpos >= dimv)
            return false;
    }
    return true;
}

bool TokenSet::token_collision(int token_id1, int orientation1, int ph1, int pv1, int token_id2, int orientation2, int ph2, int pv2) const
{
    for (int i = 0; i < tiles(token_id1); i++) {
        int hpos1 = ph1 + posh(token_id1, i, orientation1);
        int vpos1 = pv1 + posv(token_id1, i, orientation1);
        for (int j = 0; j < tiles(token_id2); j++) {
            int hpos2 = ph2 + posh(token_id2, j, orientation2);
            int vpos2 = pv2 + posv(token_id2, j, orientation2);
            if (hpos1 == hpos2 && vpos1 == vpos2)
                return true;
        }
    }
    return false;
}

bool TokenSet::tile_at(int token_id, int orientation, int ph, int pv) const
{
    for (int i = 0; i < tiles(token_id); i++) {
        if (posh(token_id, i, orientation) == ph && posv(token_id, i, orientation) == pv)
            return true;
    }
    return false;
}

float TokenSet::horz_center(int token_id, int orientation, float pitch) const
{
    int maxh = -1000;
    int minh = 1000;
    for (int i = 0; i < tiles(token_id); i++) {
        maxh = std::max(maxh, posh(token_id, i, orientation));
        minh = std::min(minh, posh(token_id, i, orientation));
    }
    return (pitch * ((float) (maxh + minh))) / 2.0f;
}

float TokenSet::vert_center(int token_id, int orientation, float pitch) const
{
    int maxv = -1000;
    int minv = 1000;
    for (int i = 0; i < tiles(token_id); i++) {
        maxv = std::max(maxv, posv(token_id, i, orientation));
        minv = std::min(minv, posv(token_id, i, orientation));
    }
    return (pitch * ((float) (maxv + minv))) / 2.0f;
}

void TokenSet::advance(float seconds)
{
    for (int i = 0; i < m_tokens; i++) {
        m_token[i].advance(seconds);
    }
}

CadModel TokenSet::model(int token_id, float animation_id) const
{
    return m_token[token_id].model(animation_id);
}

const float* TokenSet::data(int token_id)
{
    return m_token[token_id].data();
}

void TokenSet::set_position(int token_id, float posx, float posy, float posz, float seconds)
{
    m_token[token_id].set_position(posx, posy, posz, seconds);
}

void TokenSet::set_dock_position(int token_id, int dock_id, float pitch, float seconds)
{
    Dock dock(pitch);
    float posx = dock.posx(dock_id) - horz_center(token_id, 0, pitch);
    float posz = dock.posz(dock_id) + vert_center(token_id, 0, pitch);
    m_token[token_id].set_position(posx, 0.0, posz, seconds);
}

void TokenSet::set_angle_ax(int token_id, float angle, float seconds)
{
    m_token[token_id].set_angle_ax(angle, seconds);
}

void TokenSet::set_angle_ay(int token_id, float angle, float seconds)
{
    m_token[token_id].set_angle_ay(angle, seconds);
}

void TokenSet::set_angle_az(int token_id, float angle, float seconds)
{
    m_token[token_id].set_angle_az(angle, seconds);
}


