//
// atomic_shape.h
//

#ifndef _ATOMIC_SHAPE_H_
#define _ATOMIC_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class AtomicShape: public Shape
{
public:
    AtomicShape(float major_radius, float minor_radius, float height);
    virtual ~AtomicShape();
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
    void slice(int step);
    void add_line(float x1, float z1, float x2, float z2);
    void rotate(Float2& point, float angle) const;
    void translate(Float2& point, Float2 distance) const;
};

#endif // _ATOMIC_SHAPE_
