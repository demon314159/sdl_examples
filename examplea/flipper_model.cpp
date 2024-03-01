//
// flipper_model.cpp
//

#include "flipper_model.h"
#include "flipper_shape.h"

FlipperModel::FlipperModel(float animation_id,
                           const PaintCan& flipper_color, const PaintCan& rubber_color,
                           float r1, float r2, float length, float height,
                           float rubber_thickness, float rubber_height)
{
    add(FlipperShape(r1, r2, length, height), flipper_color, animation_id);
    add(FlipperShape(r1 + rubber_thickness, r2 + rubber_thickness, length, rubber_height), rubber_color, animation_id);
}

FlipperModel::~FlipperModel()
{
}


