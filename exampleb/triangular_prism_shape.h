//
// triangular_prism_shape.h
//

#ifndef _TRIANGULAR_PRISM_SHAPE_H_
#define _TRIANGULAR_PRISM_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TriangularPrismShape: public Shape
{
public:
    TriangularPrismShape(float length, float width, float height, float corner_radius = 0.0);
    virtual ~TriangularPrismShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_length;
    float m_width;
    float m_height;
    float m_corner_radius;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TRIANGULAR_PRISM_SHAPE_
