//
// pipe.h
//

#ifndef _PIPE_H_
#define _PIPE_H_

#include "cad_model.h"
#include "float3.h"

class Pipe
{
public:
    Pipe(float angle, Float3 position, float radius, float length, const PaintCan& color, int steps);
    ~Pipe();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float end_angle() const;
    Float3 end_position() const;

private:
    float m_angle;
    Float3 m_position;
    float m_radius;
    float m_length;
    PaintCan m_color;
    int m_steps;
};

#endif // _PIPE_H_
