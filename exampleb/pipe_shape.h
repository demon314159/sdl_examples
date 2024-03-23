//
// pipe_shape.h
//

#ifndef _PIPE_SHAPE_H_
#define _PIPE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class PipeShape: public Shape
{
public:
    PipeShape(float radius, float length, int steps);
    virtual ~PipeShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_length;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void slice(int step, float angle_i, float angle_f);

    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _PIPE_SHAPE_
