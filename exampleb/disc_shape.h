//
// disc_shape.h
//

#ifndef _DISC_SHAPE_H_
#define _DISC_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class DiscShape: public Shape
{
public:
    DiscShape(float radius, float height, int major_steps, int minor_steps, bool top_only = false, bool lit_only = false, bool unlit_only = false);
    virtual ~DiscShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_height;
    int m_major_steps;
    int m_minor_steps;
    bool m_top_only;
    bool m_lit_only;
    bool m_unlit_only;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void slice_ay(int step);
    void edge_slice(int step, float rmajor, float rminor, float ay1, float ay2);
    void rotate(Float3& point, float angle) const;
};

#endif // _DISC_SHAPE_
