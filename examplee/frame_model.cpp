//
// frame_model.cpp
//

#include "frame_model.h"
#include "brick_shape.h"
#include <cstddef>

FrameModel::FrameModel(float dimx, float dimy, float dimz, float dimb, float sill, float head, float jamb,
                       const PaintCan& paint_can, float animation_id,
                       bool no_left_side, bool no_right_side)
    : m_dimx(dimx)
    , m_dimy(dimy)
    , m_dimz(dimz)
    , m_dimb(dimb)
    , m_sill(sill)
    , m_head(head)
    , m_jamb(jamb)
    , m_paint_can(paint_can)
    , m_animation_id(animation_id)
    , m_no_left_side(no_left_side)
    , m_no_right_side(no_right_side)
{
    define_model();
}

FrameModel::~FrameModel()
{
}

void FrameModel::define_model()
{
    BrickShape jamb_shape(m_jamb, m_dimy, m_dimz, m_dimb);
    BrickShape head_shape(m_dimx, m_head, m_dimz, m_dimb);
    CadModel jamb_model = CadModel(jamb_shape, m_paint_can, m_animation_id);
    CadModel head_model = CadModel(head_shape, m_paint_can, m_animation_id);
    if (!m_no_left_side) {
        add(jamb_model, (-m_dimx + m_jamb) / 2.0, 0.0, 0.0);
    }
    if (!m_no_right_side) {
        add(jamb_model, (m_dimx - m_jamb) / 2.0, 0.0, 0.0);
    }
    add(head_model, 0.0, (m_dimy - m_head) / 2.0, 0.0);
    if (m_sill > 0.0) {
        BrickShape sill_shape(m_dimx, m_sill, m_dimz, m_dimb);
        CadModel sill_model = CadModel(sill_shape, m_paint_can, m_animation_id);
        add(sill_model, 0.0, (-m_dimy + m_sill) / 2.0, 0.0);
    }
}


