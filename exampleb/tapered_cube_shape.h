//
// tapered_cube_shape.h
//

#ifndef _TAPERED_CUBE_SHAPE_H_
#define _TAPERED_CUBE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TaperedCubeShape: public Shape
{
public:
    TaperedCubeShape(float dimx, float dimy, float dimz, float left_dx, float right_dx, float front_dz, float back_dz);
    virtual ~TaperedCubeShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_left_dx;
    float m_right_dx;
    float m_front_dz;
    float m_back_dz;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TAPERED_CUBE_SHAPE_
