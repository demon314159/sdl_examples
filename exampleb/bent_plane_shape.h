//
// bent_plane_shape.h
//

#ifndef _BENT_PLANE_SHAPE_H_
#define _BENT_PLANE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class BentPlaneShape: public Shape
{
public:
    BentPlaneShape(float dimx, float dimy, float dimz, int steps);
    virtual ~BentPlaneShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);

    void az_slice(int step);
};

#endif // _BENT_PLANE_SHAPE_
