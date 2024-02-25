//
// pole_model.cpp
//

#include "pole_model.h"
#include "pole_shape.h"

PoleModel::PoleModel(float animation_id,
                     const PaintCan& body_color, const PaintCan& bumper_color,
                     float radius, float height,
                     float bumper_thickness, float bumper_height)
{
    add(PoleShape(radius, height), body_color, animation_id);
    add(PoleShape(radius + bumper_thickness, bumper_height), bumper_color, animation_id);
}

PoleModel::~PoleModel()
{
}


