//
// hover.cpp
//

#include "hover.h"

Hover::Hover()
    : m_on(false)
    , m_piece_id(0)
    , m_offset({0.0, 0.0, 0.0})
{
}

Hover::~Hover()
{
}

bool Hover::on() const
{
    return m_on;
}

int Hover::piece_id() const
{
    return m_piece_id;
}

Float3 Hover::offset() const
{
    return m_offset;
}

void Hover::start(int piece_id, float offsetx, float offsety, float offsetz)
{
    m_piece_id = piece_id;
    m_offset = {offsetx, offsety, offsetz};
    m_on = true;
}

void Hover::stop()
{
    m_on = false;
    m_piece_id = 0;
    m_offset = {0.0, 0.0, 0.0};
}

