//
// tray_border_shape.h
//

#ifndef _TRAY_BORDER_SHAPE_H_
#define _TRAY_BORDER_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TrayBorderShape: public Shape
{
public:
    TrayBorderShape(float pitch, float width, float height, bool upper, bool lower, bool left, bool right);
    virtual ~TrayBorderShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_pitch;
    float m_width;
    float m_height;
    bool m_upper;
    bool m_lower;
    bool m_left;
    bool m_right;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TRAY_BORDER_SHAPE_
