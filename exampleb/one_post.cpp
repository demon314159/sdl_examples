//
// one_post.cpp
//

#include "one_post.h"
#include "pi.h"
#include "plane_shape.h"
#include "cone_shape.h"
#include "toroid_shape.h"
#include "pipe_shape.h"
#include "convex_plane_shape.h"
#include "cylinder_shape.h"
#include <math.h>

#include <stdio.h>


OnePost::OnePost(Float2 p, float radius, float height, const PaintCan& color,
                 float reflectivity, int steps)
    : m_p(p)
    , m_radius(radius)
    , m_height(height)
    , m_color(color)
    , m_steps(steps)
    , m_reflector(p, radius, 0.0, 360.0, reflectivity)
{
}

OnePost::~OnePost()
{
}

void OnePost::collide(Ball* ball) const
{
    m_reflector.collide(ball);
}

CadModel OnePost::model(float animation_id) const
{
    CadModel mm;

    float rbumper = 0.00211;
    float r0_post = 0.4 * m_radius;
    float r1_post = r0_post;
    float r2_post = r0_post;
    float r3_post = 0.25 * r2_post;
    float h1_post = 0.863636 * m_height;
    float h2_post = 1.1363636 * m_height;
    float h3_post = 1.54545 * m_height;

    CadModel big_post(ConeShape(r0_post, r1_post, h1_post, m_steps), m_color, animation_id);
    CadModel big_post2(ConeShape(r1_post, r1_post, h2_post - h1_post, m_steps), m_color, animation_id);
    CadModel big_post3(ConeShape(r1_post, r3_post, h3_post - h2_post, m_steps), m_color, animation_id);
    big_post.add(big_post2, 0.0, h1_post, 0.0);
    big_post.add(big_post3, 0.0, h2_post, 0.0);
    CadModel b(ToroidShape(m_radius - rbumper, rbumper, m_steps, 0.0, 360.0), PaintCan(1.0, 1.0, 1.0), animation_id);
    mm.add(big_post, m_p.v1, 0.0, m_p.v2);
    mm.add(b, m_p.v1, m_height, m_p.v2);
    return mm;
}


