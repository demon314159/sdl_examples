//
// rounded_plane_shape.h
//

#ifndef _ROUNDED_PLANE_SHAPE_H_
#define _ROUNDED_PLANE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class RoundedPlaneShape: public Shape
{
public:
    RoundedPlaneShape(float dimx, float dimy, float dimz, float left_bend_radius, float right_bend_radius, int steps);
    virtual ~RoundedPlaneShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_dimy;
    float m_dimz;
    float m_left_bend_radius;
    float m_right_bend_radius;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);

    void add_round(float xc, float zc, float radius, float angle_i, float angle_f);
#ifdef NEVERMORE
    void ax_slice(int step);
    void az_slice(int step);
    void ay_slice(int step);
    void bend_slice(int step, float ay1, float ay2, bool top);
    Float3 rotated(Float3 point, float angle) const;
    Float3 translated(Float3 point, Float3 distance) const;
#endif
};

#endif // _ROUNDED_PLANE_SHAPE_
