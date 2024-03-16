//
// state.h
//

#ifndef STATE_H_
#define STATE_H_

#include "float3.h"

class State
{
public:
    State(void);
    State(const Float2& position, const Float2& velocity);

    State operator * (double scale) const;
    State operator + (const State& s) const;
    State operator - (const State& s) const;

    Float2 position(void) const;    // Linear Position
    Float2 velocity(void) const;    // Linear Velocity

    void set_position(const Float2& position);
    void set_velocity(const Float2& velocity);
    void rotate_frame(float angle);
    void translate_velocity_frame(Float2 velocity);
    void translate_frame(Float2 distance);

protected:
    Float2 m_position;   // Linear Position
    Float2 m_velocity;   // Linear Velocity
};

#endif // STATE_H_

