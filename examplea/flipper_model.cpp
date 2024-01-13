//
// flipper_model.cpp
//

#include "flipper_model.h"
#include "flipper_shape.h"

FlipperModel::FlipperModel(float animation_id,
                           const PaintCan& flipper_color, const PaintCan& bumper_color,
                           float r1, float r2, float length, float height,
                           float bumper_thickness, float bumper_height)
{
    add(FlipperShape(r1, r2, length, height), flipper_color, animation_id);
    add(FlipperShape(r1 + bumper_thickness, r2 + bumper_thickness, length, bumper_height), bumper_color, animation_id);
}

FlipperModel::~FlipperModel()
{
}


