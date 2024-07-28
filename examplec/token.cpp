//
// token.cpp
//

#include "token.h"

Token::Token()
    : m_tiles(0)
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


