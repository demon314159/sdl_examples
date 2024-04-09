//
// rounded_cube_shape.h
//

#ifndef _ROUNDED_CUBE_SHAPE_H_
#define _ROUNDED_CUBE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class RoundedCubeShape: public Shape
{
public:
    RoundedCubeShape(float dimx, float dimy, float dimz, float bend_radius, int steps,
                     bool lit_only = false, bool unlit_only = false);
    virtual ~RoundedCubeShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_bend_radius;
    int m_steps;
    bool m_lit_only;
    bool m_unlit_only;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void ax_slice(int step);
    void az_slice(int step);
    void ay_slice(int step);
    void bend_slice(int step, float ay1, float ay2, bool top);
    Float3 rotated(Float3 point, float angle) const;
    Float3 translated(Float3 point, Float3 distance) const;
};

#endif // _ROUNDED_CUBE_SHAPE_
