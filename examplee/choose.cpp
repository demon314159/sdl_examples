//
// choose.cpp
//

#include "choose.h"
#include "math.h"
#include "cylinder_shape.h"

Choose::Choose(float dimx, float dimy, float dimz, const PaintCan& marker_color)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_color(marker_color)
    , m_first_selected(false)
    , m_second_selected(false)
    , m_first_choice({0, 0, 0})
    , m_second_choice({0, 0, 0})
{
}

Choose::~Choose()
{
}

void Choose::select_no_choice()
{
    m_first_selected = false;
    m_second_selected = false;
    m_first_choice = {0, 0, 0};
    m_second_choice = {0, 0, 0};
}

void Choose::select_choice(Int3 c)
{
    if (m_first_selected && !m_second_selected) {
        m_second_selected = true;
        m_second_choice = c;
    } else {
        m_first_selected = true;
        m_second_selected = false;
        m_first_choice = c;
        m_second_choice = {0, 0, 0};
    }
}

CadModel Choose::model(float animation_id) const
{
    CadModel cm(CylinderShape(m_dimx * 0.45f, m_dimy / 8.0, 100), m_color, animation_id);
    return cm;
}

bool Choose::new_element_chosen(Int3& pos, int& width, int& orientation) const
{
    if (m_first_selected && m_second_selected) {
        int xspan = m_second_choice.v1 - m_first_choice.v1;
        int zspan = m_second_choice.v3 - m_first_choice.v3;
        pos = m_first_choice;
        if (zspan > 0) {
            orientation = 3;
            width = zspan + 1;
        } else if (xspan < 0) {
            orientation = 2;
            width = -xspan + 1;
        } else if (zspan < 0) {
            orientation = 1;
            width = -zspan + 1;
        } else if (xspan > 0) {
            orientation = 0;
            width = xspan + 1;
        } else {
            orientation = 0;
            width = 1;
        }
        return true;
    } else {
        return false;
    }
}

const float* Choose::data()
{
    m_animation.unity();
    if (m_first_selected && !m_second_selected) {
        float x = m_dimx * (float) m_first_choice.v1;
        float y = m_dimy * (float) m_first_choice.v2;
        float z = m_dimz * (float) m_first_choice.v3;
        y -= (m_dimy / 2.0 - m_dimy / 16.0);
        m_animation.translate(x, y, z);
    } else {
        m_animation.translate(0.0, -5.0, 0.0);
    }
    return m_animation.data();
}

