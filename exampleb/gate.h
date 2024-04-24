//
// gate.h
//

#ifndef _GATE_H_
#define _GATE_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"

class Gate
{
public:
    Gate(Float2 position, float width, float length, float height, float angle,
            const PaintCan& color, float reflectivity, int steps);
    ~Gate();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_position;
    float m_width;
    float m_length;
    float m_height;
    float m_angle;
    PaintCan m_color;
    int m_steps;
};

#endif // _TWO_POST_H_
