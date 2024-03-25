//
// straight_diode_strip.h
//

#ifndef _STRAIGHT_DIODE_STRIP_H_
#define _STRAIGHT_DIODE_STRIP_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "straight_diode_reflector.h"

class StraightDiodeStrip
{
public:
    StraightDiodeStrip(float angle, Float3 position, float length, float height, const PaintCan& color, float reflectivity);

    ~StraightDiodeStrip();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    void collide(Ball* ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_height;
    PaintCan m_color;
    StraightDiodeReflector m_reflector;
};

#endif // _STRAIGHT_DIODE_STRIP_H_
