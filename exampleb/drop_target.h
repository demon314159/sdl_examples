//
// drop_target.h
//

#ifndef _DROP_TARGET_H_
#define _DROP_TARGET_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class DropTarget
{
public:
    DropTarget(Float2 position, float angle, float width, float height, float thickness,
               const PaintCan& color, float reflectivity, int steps);
    ~DropTarget();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_position;
    float m_angle;
    float m_width;
    float m_height;
    float m_thickness;
    PaintCan m_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
};

#endif // _DROP_TARGET_H_
