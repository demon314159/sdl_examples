//
// toroid_shape.h
//

#ifndef _TOROID_SHAPE_H_
#define _TOROID_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class ToroidShape: public Shape
{
public:
    ToroidShape(float major_radius, float minor_radius, int steps, float major_angle_i = 0.0, float major_angle_f = 360.0, float minor_angle_i = 0.0, float minor_angle_f = 360.0);
    virtual ~ToroidShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_major_radius;
    float m_minor_radius;
    int m_steps;
    float m_major_angle_i;
    float m_major_angle_f;
    float m_minor_angle_i;
    float m_minor_angle_f;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void ay_slice(int step, int steps);
    void ax_slice(int step, int steps, float major_a1, float major_a2);
    void one_square(float major_a1, float major_a2, float minor_a1, float minor_a2);
    Float3 rotate_ay(Float3 p, float angle) const;
};

#endif // _TOROID_SHAPE_
