//
// cylinder_shape.h
//

#ifndef _CYLINDER_SHAPE_H_
#define _CYLINDER_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class CylinderShape: public Shape
{
public:
    CylinderShape(float radius, float height, int steps);
    virtual ~CylinderShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_height;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void slice(int step, float r, float theta_i, float theta_f);

    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _CYLINDER_SHAPE_
