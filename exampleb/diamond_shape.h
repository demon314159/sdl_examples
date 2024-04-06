//
// diamond_shape.h
//

#ifndef _DIAMOND_SHAPE_H_
#define _DIAMOND_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class DiamondShape: public Shape
{
public:
    DiamondShape(float length, float width, float height);
    virtual ~DiamondShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_length;
    float m_width;
    float m_height;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _DIAMOND_SHAPE_
