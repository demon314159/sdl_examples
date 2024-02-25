//
// bumper_shape.h
//

#ifndef _BUMPER_SHAPE_H_
#define _BUMPER_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"


class BumperShape: public Shape
{
public:
    BumperShape(float radius, float height);
    virtual ~BumperShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_height;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void define_cylinder();
    void cylinder_slice(int step, int steps, float r, float theta_i, float theta_f);

    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _BUMPER_SHAPE_
