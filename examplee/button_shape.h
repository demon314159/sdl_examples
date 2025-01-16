//
// button_shape.h
//

#ifndef _BUTTON_SHAPE_H_
#define _BUTTON_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"
#include "pi.h"

class ButtonShape: public Shape
{
public:
    ButtonShape(float radius, float height, float minor_radius, int steps, int minor_steps, float texture_id = 0);
    virtual ~ButtonShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;
    bool uses_texture() const override;

private:
    float m_height;
    float m_major_radius;
    float m_minor_radius;
    int m_major_steps;
    int m_minor_steps;
    float m_texture_id;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void button_slice(int step, int steps);
    void slice_slice(int step, int steps, const Float3& pa, const Float3& pb, bool top, bool bottom);
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false, float texture_id = 0.0);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false, float texture_id = 0.0);
    Float3 rotate_ay(Float3 p, float angle) const;
};

#endif // _BUTTON_SHAPE_
