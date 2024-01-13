//
// flipper_shape.h
//

#ifndef _FLIPPER_SHAPE_H_
#define _FLIPPER_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class FlipperShape: public Shape
{
public:
    FlipperShape(float r1, float r2, float length, float height);
    virtual ~FlipperShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_r1;
    float m_r2;
    float m_length;
    float m_height;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void define_cylinders();
    void define_walls();
    void cylinder_slice(int step, int steps, float r, float theta_i, float theta_f, float xoff);


    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _FLIPPER_SHAPE_
