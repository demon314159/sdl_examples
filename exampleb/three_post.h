//
// three_post.h
//

#ifndef _THREE_POST_H_
#define _THREE_POST_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class ThreePost
{
public:
    ThreePost(Float2 p1, Float2 p2, Float2 p3, float radius, float height,
              const PaintCan& color, const PaintCan& face_color,
              float reflectivity, int steps);
    ~ThreePost();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p1;
    Float2 m_p2;
    Float2 m_p3;
    float m_radius;
    float m_height;
    PaintCan m_color;
    PaintCan m_face_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    ConvexReflector m_reflector3;
    StraightReflector m_reflector4;
    StraightReflector m_reflector5;
    StraightReflector m_reflector6;
};

#endif // _THREE_POST_H_
