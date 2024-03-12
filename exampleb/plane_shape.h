//
// plane_shape.h
//

#ifndef _PLANE_SHAPE_H_
#define _PLANE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class PlaneShape: public Shape
{
public:
    PlaneShape(float dimx, float dimz, float texture_id = 0.0);
    virtual ~PlaneShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;
    bool uses_texture() const override;

private:
    float m_dimx;
    float m_dimz;
    float m_texture_id;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float2 t1, Float2 t2, Float2 t3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, Float2 t1, Float2 t2, Float2 t3, Float2 t4, bool flip = false);
};

#endif // _PLANE_SHAPE_
