//
// straight_kicker.h
//

#ifndef _STRAIGHT_KICKER_H_
#define _STRAIGHT_KICKER_H_

#include "float3.h"
#include "ball.h"
#include "perimeter.h"

class StraightKicker
{
public:
    StraightKicker(Float2 p1, Float2 p2, float radius, float velocity);
    ~StraightKicker();
    void update_perimeter();

    bool within_range(const Ball* ball) const;
    void collide(Ball* ball) const;
    void translate(Float2 distance);
    void rotate(float angle);
    Float2 position() const;
    float length() const;
    float angle() const;

private:
    Perimeter m_perimeter;
    Float2 m_position;
    float m_length;
    float m_velocity;
    float m_angle;
    void translate(Float2& point, Float2 distance) const;
    void rotate(Float2& point, float angle) const;
};

#endif // _STRAIGHT_KICKER_H_
