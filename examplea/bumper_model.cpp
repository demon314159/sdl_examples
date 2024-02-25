//
// bumper_model.cpp
//

#include "bumper_model.h"
#include "bumper_shape.h"

BumperModel::BumperModel(float animation_id,
                         const PaintCan& body_color, const PaintCan& bumper_color,
                         float radius, float height,
                         float bumper_thickness, float bumper_height)
{
    add(BumperShape(radius, height), body_color, animation_id);
    add(BumperShape(radius + bumper_thickness, bumper_height), bumper_color, animation_id);
}

BumperModel::~BumperModel()
{
}


