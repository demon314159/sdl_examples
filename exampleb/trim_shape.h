//
// trim_shape.h
//

#ifndef _TRIM_SHAPE_H_
#define _TRIM_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TrimShape: public Shape
{
public:
    TrimShape(float major_radius, float minor_radius, float height, int steps);
    virtual ~TrimShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_major_radius;
    float m_minor_radius;
    float m_height;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void slice_ay(int step);
};

#endif // _TRIM_SHAPE_
