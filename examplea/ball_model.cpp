//
// ball_model.cpp
//

#include "ball_model.h"
#include "sphere_shape.h"

BallModel::BallModel(float animation_id,
                     const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
                     float radius)
{
    float angle = 20.0;
    float top_lattitude = angle * PI / 180.0;
    float bottom_lattitude = -angle * PI / 180.0;
    add(SphereShape(radius, -PI / 2.0, bottom_lattitude), bottom_color, animation_id);
    add(SphereShape(radius, bottom_lattitude, top_lattitude), middle_color, animation_id);
    add(SphereShape(radius, top_lattitude, PI / 2.0), top_color, animation_id);
}

BallModel::~BallModel()
{
}


