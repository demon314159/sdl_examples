//
// concave_plane_shape.h
//

#ifndef _CONCAVE_PLANE_SHAPE_H_
#define _CONCAVE_PLANE_SHAPE_H_

#include "shape.h"
#include "float3.h"
#include "facet.h"

class ConcavePlaneShape: public Shape
{
public:
    ConcavePlaneShape(float radius, float angle_i, float angle_f, float height, int steps);
    virtual ~ConcavePlaneShape();
    int facets() const override;
    Facet facet(int facet_ix) const override;

private:
    float m_radius;
    float m_angle_i;
    float m_angle_f;
    float m_height;
    int m_steps;
    bool m_size_known;
    int m_facet_count;
    Facet *m_facet;

    void define_shape();
    void add_face(Float3 v1, Float3 v2, Float3 v3, bool flip = false);
    void add_face(Float3 v1, Float3 v2, Float3 v3, Float3 v4, bool flip = false);

    void slice(int step, float r, float theta_i, float theta_f);
};

#endif // _CONCAVE_PLANE_SHAPE_
