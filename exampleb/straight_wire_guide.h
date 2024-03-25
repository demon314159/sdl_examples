//
// straight_wire_guide.h
//

#ifndef _STRAIGHT_WIRE_GUIDE_H_
#define _STRAIGHT_WIRE_GUIDE_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class StraightWireGuide
{
public:
    StraightWireGuide(float angle, Float3 position, float length, float height, float diameter, const PaintCan& color, int reflectivity, int steps);
    ~StraightWireGuide();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    float height() const;
    float diameter() const;
    void collide(Ball* ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_height;
    float m_diameter;
    PaintCan m_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _STRAIGHT_WIRE_GUIDE_H_
