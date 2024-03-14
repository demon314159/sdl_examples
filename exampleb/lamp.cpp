//
// lamp.cpp
//

#include "lamp.h"
#include "plane_shape.h"

Lamp::Lamp(float lamp_id, Float3 position, Float2 size, const PaintCan& on_color, const PaintCan& off_color)
    : m_state(false)
    , m_lamp_id(lamp_id)
    , m_position(position)
    , m_size(size)
    , m_on_color(on_color)
    , m_off_color(off_color)
{
}

Lamp::~Lamp()
{
}

CadModel Lamp::model() const
{
    CadModel cm;
    CadModel lamp(PlaneShape(m_size.v1, m_size.v2), m_off_color, m_lamp_id);
    cm.add(lamp, m_position.v1, m_position.v2, m_position.v3);
    return cm;
}


