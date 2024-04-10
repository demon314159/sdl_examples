//
// one_post.h
//

#ifndef _ONE_POST_H_
#define _ONE_POST_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class OnePost
{
public:
    OnePost(Float2 p, float radius, float height, const PaintCan& color,
            float reflectivity, int steps);
    ~OnePost();

    CadModel model(float animation_id) const;
    void collide(Ball* ball) const;

private:
    Float2 m_p;
    float m_radius;
    float m_height;
    PaintCan m_color;
    int m_steps;
    ConvexReflector m_reflector;
};

#endif // _ONE_POST_H_
