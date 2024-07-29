//
// tile_shape.h
//

#ifndef _TILE_SHAPE_H_
#define _TILE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class TileShape: public Shape
{
public:
    TileShape(float pitch, float width, float height, float border,
              bool upper, bool lower, bool left, bool right,
              bool upper_left, bool upper_right, bool lower_left, bool lower_right);
    virtual ~TileShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_pitch;
    float m_width;
    float m_height;
    float m_border;
    bool m_upper;
    bool m_lower;
    bool m_left;
    bool m_right;
    bool m_upper_left;
    bool m_upper_right;
    bool m_lower_left;
    bool m_lower_right;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);
};

#endif // _TILE_SHAPE_
