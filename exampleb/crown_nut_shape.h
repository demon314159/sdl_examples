//
// crown_nut_shape.h
//

#ifndef _CROWN_NUT_SHAPE_H_
#define _CROWN_NUT_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class CrownNutShape: public Shape
{
public:
    CrownNutShape(float radius, float height, int major_steps, int minor_steps);
    virtual ~CrownNutShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_height;
    int m_major_steps;
    int m_minor_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void sphere_slice(int step, int steps, float r, float lattitude_i, float lattitude_f);
    void ring_slice(int step, int steps, float r, float lattitude1, float lattitude2);
    void slice_ay(int step, int steps);
};

#endif // _CROWN_NUT_SHAPE_SHAPE_
