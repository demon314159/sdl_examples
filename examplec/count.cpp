//
// count.cpp
//

#include "count.h"
#include "plane_shape.h"

Count::Count(int digits, int initial_value, float width, float height, const Float2& position)
    : m_digits(digits)
    , m_count(initial_value)
    , m_width(width)
    , m_height(height)
    , m_position(position)
    , m_data(new float[digits])
{
}

Count::~Count()
{
    delete [] m_data;
}

int Count::digits() const
{
    return m_digits;
}

int Count::count() const
{
    return m_count;
}

void Count::set_value(int v)
{
    m_count = v;
}

const float* Count::data()
{
    int value = m_count;
    for (int i = 0; i < m_digits; i++) {
        bool blank = (value == 0) && (i > 0);
        int v = value % 10;
        value = value / 10;
        m_data[i] = blank ? 0.909090909 : 0.09090909 * (float) v;
    }
    return m_data;
}

CadModel Count::model(float animation_id, float texture_id) const
{
    float w = m_width / (float) m_digits;
    CadModel cm;
    for (int i = 0; i < m_digits; i++) {
        CadModel single(PlaneShape(w, m_height, texture_id, {0.0, 0.0}, {0.09090909, 1.0}), PaintCan(0.0, 0.0, 0.0), animation_id + (float) i);
        cm.add(single, m_position.v1 - w * (float) i + m_width / 2.0, 0.0, -m_position.v2);
    }
    return cm;
}
