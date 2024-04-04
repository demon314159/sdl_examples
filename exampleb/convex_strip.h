//
// convex_strip.h
//

#ifndef _CONVEX_STRIP_H_
#define _CONVEX_STRIP_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"

class ConvexStrip
{
public:
    ConvexStrip(float angle_i, float angle_f, Float3 position, float radius, float height, const PaintCan& color, float reflectivity, int steps);

    ~ConvexStrip();

    CadModel model(float animation_id) const;
    float angle_i() const;
    float angle_f() const;
    Float3 position() const;
    float radius() const;
    void collide(Ball* ball) const;

private:
    float m_angle_i;
    float m_angle_f;
    Float3 m_position;
    float m_radius;
    float m_height;
    float m_steps;
    PaintCan m_color;
    ConvexReflector m_reflector;
};

#endif // _CONVEX_STRIP_H_
