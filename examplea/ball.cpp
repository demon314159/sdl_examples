//
// ball.cpp
//

#include "ball.h"
#include "sphere_shape.h"
#include "pi.h"
#include "math.h"

Ball::Ball(float radius, const PaintCan& top_color, const PaintCan& middle_color, const PaintCan& bottom_color)
    : m_radius(radius)
    , m_top_color(top_color)
    , m_middle_color(middle_color)
    , m_bottom_color(bottom_color)
    , m_acceleration({0.0, 0.0})
    , m_state()
    , m_orientation()
{
}

Ball::~Ball()
{
}

CadModel Ball::model(float animation_id) const
{
    float angle = 20.0;
    float top_lattitude = angle * PI / 180.0;
    float bottom_lattitude = -angle * PI / 180.0;
    CadModel mm;
    mm.add(SphereShape(m_radius, -PI / 2.0, bottom_lattitude), m_bottom_color, animation_id);
    mm.add(SphereShape(m_radius, bottom_lattitude, top_lattitude), m_middle_color, animation_id);
    mm.add(SphereShape(m_radius, top_lattitude, PI / 2.0), m_top_color, animation_id);
    return mm;
}

void Ball::advance(float seconds)
{

float last_angle = 0.0;

    State next = next_state(seconds);
    m_orientation = next_orientation(next);
    m_state = next;
    if (m_state.position().v2 > 85.0) {
        set_position({1.0, 10.0});
    }
}

float Ball::radius() const
{
    return m_radius;
}

Float2 Ball::position() const
{
    return m_state.position();
}

Float2 Ball::velocity() const
{
    return m_state.velocity();
}

Float2 Ball::acceleration() const
{
    return m_acceleration;
}

void Ball::set_position(Float2 position)
{
    m_state.set_position(position);
}

void Ball::set_velocity(Float2 velocity)
{
    m_state.set_velocity(velocity);
}

void Ball::set_acceleration(Float2 acceleration)
{
    m_acceleration = acceleration;
}

void Ball::rotate_frame(float angle)
{
    m_state.rotate_frame(angle);
}

void Ball::translate_velocity_frame(Float2 velocity)
{
    m_state.translate_velocity_frame(velocity);
}

void Ball::translate_frame(Float2 distance)
{
    m_state.translate_frame(distance);
}

Matrix4x4 Ball::animation_matrix() const
{
    Matrix4x4 mm;
    mm.unity();
    mm.translate(m_state.position().v1, 0.0, m_state.position().v2);

    // Multipy mm times the rotation matrix
    mm = mm * m_orientation.rotation_matrix();
    return mm;
}

State Ball::rates(const State& state) const
{
    State r(state.velocity(), m_acceleration);
    return r;
}

State Ball::next_state(double dt) const
{
    State r1, a1, e1;
    State r2, a2, e2;
    State r3, a3, e3;
    State r4, a4;
    State delta;

    r1 = rates(m_state);
    a1 = r1 * dt;
    e1 = m_state + a1 * 0.5;

    r2 = rates(e1);
    a2 = r2 * dt;
    e2 = m_state + a2 * 0.5;

    r3 = rates(e2);
    a3 = r3 * dt;
    e3 = m_state + a3;

    r4 = rates(e3);
    a4 = r4 * dt;

    delta = (a1 + a2 + a2 + a3 + a3 + a4) * (1.0 / 6.0);
    return m_state + delta;
}

Quaternion Ball::next_orientation(const State& next) const
{
    double deltax = next.position().v1 - m_state.position().v1;
    double deltaz = next.position().v2 - m_state.position().v2;
    double distance = sqrt(deltax * deltax + deltaz * deltaz);
    double last_angle = (distance / m_radius) * (180.0 / PI);
    float vx = next.velocity().v1;
    float vz = next.velocity().v2;
    double v = sqrt(vx * vx + vz * vz);
    Quaternion t = m_orientation;
    if (v > 0.0) {
        float ta = vz / v;
        float tb = -vx / v;
        // Rotate m_orienation quaternion by last_angle and axes and normalize it
        Quaternion qa((float) last_angle, {ta, 0.0, tb});
        t = t * qa;
        t.normalize();
    }
    return t;
}

