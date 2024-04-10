//
// flat_rail_shape.h
//

#ifndef _FLAT_RAIL_SHAPE_H_
#define _FLAT_RAIL_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class FlatRailShape: public Shape
{
public:
    FlatRailShape(float length, float width, float thickness, float bend_radius,
                  float height, int steps);
    virtual ~FlatRailShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_length;
    float m_width;
    float m_thickness;
    float m_bend_radius;
    float m_height;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void slice(int step, float r, float theta_i, float theta_f);

    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void box_shape(float dimx, float dimy, float dimz);
    void ay_slice(int step, float angle, float l1);
};

#endif // _FLAT_RAIL_SHAPE_
