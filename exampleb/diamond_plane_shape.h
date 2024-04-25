//
// diamond_plane_shape.h
//

#ifndef _DIAMOND_PLANE_CUBE_SHAPE_H_
#define _DIAMOND_PLANE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class DiamondPlaneShape: public Shape
{
public:
    DiamondPlaneShape(float dimx, float dimy, float dimz, float diamond_dimx, float diamond_dimz);
    virtual ~DiamondPlaneShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_diamond_dimx;
    float m_diamond_dimz;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _DIAMOND_PLANE_SHAPE_
