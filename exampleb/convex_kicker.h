//
// convex_kicker.h
//

#ifndef _CONVEX_KICKER_H_
#define _CONVEX_KICKER_H_

#include "float3.h"
#include "ball.h"
#include "perimeter.h"

class ConvexKicker
{
public:
    ConvexKicker(float radius, float velocity);
    ~ConvexKicker();
    void update_perimeter();

    bool angle_within_range(float angle) const;
    bool within_distance(const Ball* ball) const;
    bool collide(Ball* ball) const;
    void translate(Float2 distance);
    void rotate(float angle);

private:
    Perimeter m_perimeter;
    Float2 m_position;
    float m_radius;
    float m_velocity;
    float m_angle_i;
    float m_angle_f;

    void translate(Float2& point, Float2 distance) const;
    void rotate(Float2& point, float angle) const;
};

#endif // _CONVEX_KICKER_H_
