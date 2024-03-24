//
// pipe_elbow_shape.h
//

#ifndef _PIPE_ELBOW_SHAPE_H_
#define _PIPE_ELBOW_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class PipeElbowShape: public Shape
{
public:
    PipeElbowShape(float radius, float bend_radius, float bend_angle, int steps, int bend_steps);
    virtual ~PipeElbowShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_bend_radius;
    float m_bend_angle;
    int m_steps;
    int m_bend_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void bend_slice(int step, float ay_i, float ay_f);
    void slice(int step, float ax_i, float ax_f, float ay1, float ay2);
    void translate(Float3& point, float x, float y, float z) const;
    void rotate_ay(Float3& point, float angle) const;

    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _PIPE_ELBOW_SHAPE_
