//
// top_panel_shape.h
//

#ifndef _TOP_PANEL_SHAPE_H_
#define _TOP_PANEL_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TopPanelShape: public Shape
{
public:
    TopPanelShape(float dimx, float radius, float angle_i, float angle_f, Float2 focus, float left_x, float left_z, int steps);
    virtual ~TopPanelShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_dimx;
    float m_radius;
    float m_angle_i;
    float m_angle_f;
    Float2 m_focus;
    float m_left_x;
    float m_left_z;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
    void slice(int step);
};

#endif // _TOP_PANEL_SHAPE_
