//
// bottom_panel_shape.h
//

#ifndef _BOTTOM_PANEL_SHAPE_H_
#define _BOTTOM_PANEL_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class BottomPanelShape: public Shape
{
public:
    BottomPanelShape(float x1, float x2, float x3, float x4, float z1, float z2, float z3);
    virtual ~BottomPanelShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_x1;
    float m_x2;
    float m_x3;
    float m_x4;
    float m_z1;
    float m_z2;
    float m_z3;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _BOTTOM_PANEL_SHAPE_
