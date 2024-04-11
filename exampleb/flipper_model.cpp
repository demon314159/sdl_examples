//
// flipper_model.cpp
//

#include "flipper_model.h"
#include "flipper_shape.h"

FlipperModel::FlipperModel(float animation_id,
                           const PaintCan& flipper_color, const PaintCan& rubber_color,
                           float r1, float r2, float length, float height,
                           float rubber_thickness, float rubber_height, int steps,
                           bool no_hat)
{
    add(FlipperShape(r1, r2, length, height, steps), flipper_color, animation_id);
    CadModel rubber(FlipperShape(r1 + rubber_thickness, r2 + rubber_thickness, length, rubber_height, steps), rubber_color, animation_id);
    add(rubber, 0.0, rubber_height / 2.0, 0.0);
    if (!no_hat) {
        float k = 0.80;
        float k2 = k * 0.9;
        float k3 = k2 * k;
        float k4 = k3 * k;
        float t =  0.0005;

        CadModel fs1(FlipperShape(r1 * k2, r2 * k2, length, t, steps), flipper_color, animation_id);
        CadModel fs2(FlipperShape(r1 * k3, r2 * k3, length, t, steps), flipper_color, animation_id);
        CadModel fs3(FlipperShape(r1 * k4, r2 * k4, length, t, steps), flipper_color, animation_id);
        add(fs1, 0.0, t / 2.0 + height / 2.0, 0.0);
        add(fs2, 0.0, t + t / 2.0 +height / 2.0, 0.0);
        add(fs3, 0.0, 2.0 * t + t / 2.0 + height / 2.0, 0.0);
    }
}

FlipperModel::~FlipperModel()
{
}


