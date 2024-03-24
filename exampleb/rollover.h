//
// rollover.h
//

#ifndef _ROLLOVER_H_
#define _ROLLOVER_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"

class Rollover
{
public:
    Rollover(float angle, Float3 position, float length, float width, float diameter, const PaintCan& color, int steps);
    ~Rollover();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    float width() const;
    float diameter() const;
    void collide(const Ball* ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_width;
    float m_diameter;
    PaintCan m_color;
    int m_steps;
};

#endif // _ROLLOVER_H_
