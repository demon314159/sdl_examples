//
// choose.cpp
//

#include "choose.h"
#include "math.h"
#include "cylinder_shape.h"


#include <stdio.h>


#define GABLE_ANGLE 33.69006753

Choose::Choose(float dimx, float dimy, float dimz, const PaintCan& marker_color)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_color(marker_color)
    , m_first_selected(false)
    , m_first_gable_flag(false)
    , m_first_gable_orientation(0)
    , m_second_selected(false)
    , m_second_gable_flag(false)
    , m_second_gable_orientation(0)
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
    m_first_gable_flag = false;
    m_first_gable_orientation = 0;
    m_second_selected = false;
    m_second_gable_flag = false;
    m_second_gable_orientation = 0;
    m_first_choice = {0, 0, 0};
    m_second_choice = {0, 0, 0};
}

void Choose::select_choice(Int3 p, bool gable_flag, int gable_orientation)
{
    if (m_first_selected && !m_second_selected) {
        m_second_selected = true;
        m_second_gable_flag = gable_flag;
        m_second_gable_orientation = gable_orientation;
        m_second_choice = p;
    } else {
        m_first_selected = true;
        m_first_gable_flag = gable_flag;
        m_first_gable_orientation = gable_orientation;
        m_second_selected = false;
        m_first_choice = p;
        m_second_choice = {0, 0, 0};
    }
}

CadModel Choose::model(float animation_id) const
{
    CadModel cm(CylinderShape(m_dimx * 0.45f, m_dimy / 7.0, 100), m_color, animation_id);
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
        if (m_first_gable_flag) {
            m_animation.translate(x, y - m_dimy / 2.0, z);
            if (m_first_gable_orientation == 3) {
                m_animation.rotate_ax(-GABLE_ANGLE);
            } else if (m_first_gable_orientation == 2) {
                m_animation.rotate_az(-GABLE_ANGLE);
            } else if (m_first_gable_orientation == 1) {
                m_animation.rotate_ax(GABLE_ANGLE);
            } else {
                m_animation.rotate_az(GABLE_ANGLE);
            }
        } else {
            m_animation.translate(x, y, z);
        }
    } else {
        m_animation.translate(0.0, -m_dimy / 2.0 - m_dimy / 4.0, 0.0);
    }
    return m_animation.data();
}

bool Choose::valid_roof_selection() const
{
    return m_first_gable_flag && m_second_gable_flag && m_first_gable_orientation == m_second_gable_orientation;
}

void Choose::adjust_roof_orientation(Int3& p, int w, int& o)
{
    if (w == 1) {
        o = (m_first_gable_orientation - 1) & 3;
    } else {
        int normal_o = (m_first_gable_orientation - 1) & 3;
        if (normal_o == o) {
            return;
        }
        o = (o + 2) & 3;
        p = m_second_choice;
    }
}

