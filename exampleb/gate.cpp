//
// gate.cpp
//

#include "gate.h"
#include "pi.h"
#include "rounded_plane_shape.h"
#include "bent_plane_shape.h"
#include "tapered_cube_shape.h"
#include <math.h>



Gate::Gate(Float2 position, float width, float length, float height, float angle,
                 const PaintCan& color, float reflectivity, int steps)
    : m_position(position)
    , m_width(width)
    , m_length(length)
    , m_height(height)
    , m_angle(angle)
    , m_color(color)
    , m_steps(steps)
{
}

Gate::~Gate()
{
}

void Gate::collide(Ball* ball) const
{
}

CadModel Gate::model(float animation_id) const
{
    CadModel mm;

    float t1 = 0.004;
    float br1 = 0.010;
    float br2 = 0.0075;
    float wall_height = m_height - 2.0 * br2;

    CadModel base(RoundedPlaneShape(m_width, t1, m_length, br1, 0.0, 25), m_color, animation_id);
    CadModel bend(BentPlaneShape(br2, t1, m_length, 25), m_color, animation_id);

    float x = t1 / 2.0;
    float y = wall_height / 2.0;
    float z = m_length / 2.0;
    float tz = z - 0.020;

    float top_length = m_length * 0.8;

    CadModel wall(TaperedCubeShape(t1, wall_height, m_length, 0.0, 0.0, -(m_length - top_length), 0.0), m_color, animation_id);
    CadModel top_bend(BentPlaneShape(br2, t1, top_length, 25), m_color, animation_id);
    top_bend.rotate_az(180.0);
    top_bend.translate(0.0, wall_height + br2 + br2 / 2.0, -(m_length - top_length) / 2.0);


    mm.add(base, -m_width / 2.0, t1 / 2.0, 0.0);
    mm.add(bend, br2 / 2.0, br2 / 2.0, 0.0);
    mm.translate(-br2, 0.0, 0.0);
    mm.add(wall, -t1 / 2.0, wall_height / 2.0 + br2, 0.0);

    mm.add(top_bend, -br2 / 2.0 + br2 - t1, 0.0, 0.0);

    return mm;
}


