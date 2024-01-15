//
// sphere_shape.h
//

#ifndef _SPHERE_SHAPE_H_
#define _SPHERE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"
#include "pi.h"

class SphereShape: public Shape
{
public:
    SphereShape(float radius, float lattitude_i = -PI / 2.0, float lattitude_f = PI / 2.0);
    virtual ~SphereShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_lattitude_i;
    float m_lattitude_f;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void sphere_slice(int step, int steps, float r, float lattitude_i, float lattitude_f);
    void ring_slice(int step, int steps, float r, float lattitude1, float lattitude2);
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _SPHERE_SHAPE_
