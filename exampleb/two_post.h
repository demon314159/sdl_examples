//
// two_post.h
//

#ifndef _TWO_POST_H_
#define _TWO_POST_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class TwoPost
{
public:
    TwoPost(Float2 p1, Float2 p2, float radius, float height,
            const PaintCan& color, const PaintCan& face_color,
            float reflectivity, int steps);
    ~TwoPost();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p1;
    Float2 m_p2;
    float m_radius;
    float m_height;
    PaintCan m_color;
    PaintCan m_face_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _TWO_POST_H_
