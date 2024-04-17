//
// lamp.cpp
//

#include "lamp.h"
#include "plane_shape.h"

Lamp::Lamp()
    : m_lamps(0)
    , m_data(new float[MAX_LAMPS * 3])
{
}

Lamp::~Lamp()
{
    delete [] m_data;
}

float* Lamp::data() const
{
    for (int i = 0; i < m_lamps; i++) {
        Float3 lc = color(i);
        m_data[3 * i] = lc.v1;
        m_data[3 * i + 1] = lc.v2;
        m_data[3 * i + 2] = lc.v3;
    }
    return m_data;
}

int Lamp::lamps() const
{
    return m_lamps;
}

void Lamp::add(Float3 position, Float2 size, const PaintCan& on_color, const PaintCan& off_color)
{
    if (m_lamps < MAX_LAMPS) {
        m_state[m_lamps] = false;
        m_position[m_lamps] = position;
        m_size[m_lamps] = size;
        m_on_color[m_lamps] = on_color.ambient_color();
        m_off_color[m_lamps] = off_color.ambient_color();
    }
    ++m_lamps;
}

Float3 Lamp::color(int ix) const
{
    if (ix >= MAX_LAMPS) {
        return {0.0, 0.0, 0.0};
    } else {
        return m_state[ix] ? m_on_color[ix] : m_off_color[ix];
    }
}

CadModel Lamp::model(float animation_id) const
{
    CadModel cm;
    for (int i = 0; i < m_lamps; i++) {
        CadModel lamp(PlaneShape(m_size[i].v1, m_size[i].v2), m_off_color[i], animation_id + (float) i);
        cm.add(lamp, m_position[i].v1, m_position[i].v2, m_position[i].v3);
    }
    return cm;
}

void Lamp::set(int ix, bool v)
{
    if (ix < m_lamps) {
        m_state[ix] = v;
    }
}

void Lamp::toggle(int ix)
{
    if (ix < m_lamps) {
        m_state[ix] = !m_state[ix];
    }
}
