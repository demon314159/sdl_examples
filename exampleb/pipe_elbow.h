//
// pipe_elbow.h
//

#ifndef _PIPE_ELBOW_H_
#define _PIPE_ELBOW_H_

#include "cad_model.h"
#include "float3.h"

class PipeElbow
{
public:
    PipeElbow(float angle, Float3 position, float radius, float bend_angle, float bend_radius, const PaintCan& color, int steps, int bend_steps);
    ~PipeElbow();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float end_angle() const;
    Float3 end_position() const;

private:
    float m_angle;
    Float3 m_position;
    float m_radius;
    float m_bend_angle;
    float m_bend_radius;
    PaintCan m_color;
    int m_steps;
    int m_bend_steps;
};

#endif // _PIPE_ELBOW_H_
