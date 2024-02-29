//
// bouncer_model.cpp
//

#include "bouncer_model.h"
#include "cylinder_shape.h"
#include "sphere_shape.h"
#include <math.h>

BouncerModel::BouncerModel(float animation_id,
                     const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color,
                     float wall_radius, float stem_radius, float wall_height, float stem_height,
                     int steps)
{
//    add(CylinderShape(radius, height, steps), body_color, animation_id);
//    add(CylinderShape(radius + bumper_thickness, bumper_height, steps), bumper_color, animation_id);
    float r_curve = 8.0;
    float x = wall_radius;
    float theta = acos(x / r_curve);
    float y = -r_curve * sin(theta);
    CadModel dome;
    CadModel disc;
    CadModel stem;
    float dtheta = (PI / 2.0 - theta) / 3.0;

    dome.add(SphereShape(r_curve, 100, theta, theta + dtheta), bottom_color, animation_id);
    dome.add(SphereShape(r_curve, 100, theta + dtheta, theta + 2.0 * dtheta), middle_color, animation_id);
    dome.add(SphereShape(r_curve, 100, theta + 2.0 * dtheta, theta + 3.0 * dtheta), top_color, animation_id);

    disc.add(CylinderShape(wall_radius, wall_height, steps), bottom_color, animation_id);
    stem.add(CylinderShape(stem_radius, stem_height, steps), middle_color, animation_id);
    add(disc, 0.0, 0.0, 0.0);
    add(dome, 0.0, y + wall_height / 2.0, 0.0);
    add(stem, 0.0, -stem_height / 2.0, 0.0);
}

BouncerModel::~BouncerModel()
{
}


