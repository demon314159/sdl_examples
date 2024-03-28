//
// cone_shape.h
//

#ifndef _CONE_SHAPE_H_
#define _CONE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class ConeShape: public Shape
{
public:
    ConeShape(float bottom_radius, float top_radius, float height, int steps);
    virtual ~ConeShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_bottom_radius;
    float m_top_radius;
    float m_height;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void ay_slice(int step, int steps);
};

#endif // _CONE_SHAPE_
