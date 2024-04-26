//
// gate.cpp
//

#include "gate.h"
#include "pi.h"
#include "cube_shape.h"
#include "cylinder_shape.h"
#include "rounded_plane_shape.h"
#include "bent_plane_shape.h"
#include "tapered_cube_shape.h"
#include "diamond_plane_shape.h"
#include "crown_nut_shape.h"
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

    float t1 = 0.08 * m_width;
    float br1 = 0.2 * m_width;
    float br2 = 0.15 * m_width;
    float wall_height = m_height - 2.0 * br2;
    float nut_radius = 0.16 * m_width;

    CadModel nut(CrownNutShape(nut_radius, nut_radius / 2.0, 25, 25), m_color, animation_id);
    CadModel base(RoundedPlaneShape(m_width, t1, m_length, br1, 0.0, m_steps), m_color, animation_id);
    CadModel bend(BentPlaneShape(br2, t1, m_length, 25), m_color, animation_id);
    mm.add(nut, -m_width / 3.0, t1, 0.0);
    mm.add(nut, -m_width * 3.0 / 4.0, t1, -m_length / 4.0);
    mm.add(nut, -m_width * 3.0 / 4.0, t1, m_length / 4.0);
    mm.add(base, -m_width / 2.0, t1 / 2.0, 0.0);
    mm.add(bend, br2 / 2.0, br2 / 2.0, 0.0);
    mm.translate(-br2, 0.0, 0.0);

    float x = t1 / 2.0;
    float y = wall_height / 2.0;
    float z = m_length / 2.0;
    float tz = z - 0.4 * m_width;

    float top_length = m_length * 0.7;

    CadModel wall(TaperedCubeShape(t1, wall_height, m_length, 0.0, 0.0, -(m_length - top_length), 0.0), m_color, animation_id);
    mm.add(wall, -t1 / 2.0, wall_height / 2.0 + br2, 0.0);
    CadModel top_bend(BentPlaneShape(br2, t1, top_length, m_steps), m_color, animation_id);
    top_bend.rotate_az(180.0);
    top_bend.translate(0.0, wall_height + br2 + br2 / 2.0, -(m_length - top_length) / 2.0);
    mm.add(top_bend, -br2 / 2.0 + br2 - t1, 0.0, 0.0);
    mm.translate(-br2 + t1, 0.0, 0.0);

    CadModel top_base1(TaperedCubeShape(t1, m_width / 3.0, top_length, 0.0, 0.0, (m_length - top_length), 0.0), m_color, animation_id);
    top_base1.rotate_az(-90.0);
    top_base1.translate(m_width / 3.0, m_height - t1 / 2.0, -(m_length - top_length) / 2.0);
    mm.add(top_base1, -m_width /6.0, 0.0, 0.0);
    mm.translate(-m_width / 3.0, 0.0, 0.0);

    CadModel top_base2(DiamondPlaneShape(m_width / 3.0, t1, m_length, m_width / 6.0, m_length / 2.0), m_color, animation_id);

    CadModel bend3(BentPlaneShape(br2, t1, m_width / 3.0, m_steps), m_color, animation_id);
    bend3.rotate_az(90.0);
    bend3.rotate_ay(-90.0);
    bend3.translate(m_width / 6.0, m_height - br2 / 2.0, m_length / 2.0 + br2 / 2.0);
    mm.add(bend3);
    float br3 = 0.05 * m_width;
    CadModel tab(RoundedPlaneShape(m_width / 8.0, t1, m_width / 3.0, br3, 0.0, m_steps), m_color, animation_id);
    tab.rotate_az(90.0);
    tab.rotate_ay(90.0);
    tab.translate(m_width / 6.0, m_height - br2 - m_width / 16.0, m_length / 2.0 + br2 - t1 / 2.0);
    mm.add(tab);

    CadModel tongue(TaperedCubeShape(m_width * 0.9, m_height * 1.6, t1 / 2.0, m_width / 6.0, -m_width / 6.0, 0.0, 0.0), m_color, animation_id);
    tongue.rotate_ax(180.0);
    tongue.translate(m_width / 6.0, 0.0, 0.0);
    mm.add(tongue);
    CadModel pin(CylinderShape(0.00025, (m_width + br2 * 2.0) * 1.1, 25), PaintCan(0.0, 0.0, 0.0), animation_id);
    pin.rotate_az(90.0);
    pin.translate(m_width / 6.0, m_height - 2.0 * t1, 0.0);
    mm.add(pin);
    top_base2.translate(m_width / 3.0, m_height - t1 / 2.0, 0.0);
    mm.add(top_base2, -m_width /6.0, 0.0, 0.0);
    mm.translate(-m_width / 3.0, 0.0, 0.0);

    CadModel top_base3(TaperedCubeShape(t1, m_width / 3.0, m_length, 0.0, 0.0, -(m_length - top_length), 0.0), m_color, animation_id);
    top_base3.rotate_az(-90.0);
    top_base3.translate(m_width / 3.0, m_height - t1 / 2.0, 0.0);
    mm.add(top_base3, -m_width /6.0, 0.0, 0.0);
    mm.translate(-m_width / 3.0, 0.0, 0.0);

    CadModel top_bend2(BentPlaneShape(br2, t1, top_length, m_steps), m_color, animation_id);
    top_bend2.rotate_az(90.0);
    top_bend2.translate(br2 / 2.0, m_height - br2 / 2.0, -(m_length - top_length) / 2.0);
    mm.add(top_bend2, 0.0, 0.0, 0.0);

    CadModel wall2(TaperedCubeShape(t1, wall_height / 2.0, top_length, 0.0, 0.0, -top_length / 6.0, 4.0 * top_length / 6.0), m_color, animation_id);
    wall2.rotate_az(180.0);
    wall2.translate(br2 - t1 / 2.0, -wall_height / 4.0 + m_height - br2, -(m_length - top_length) / 2.0);


    mm.add(wall2, 0.0, 0.0, 0.0);
    mm.translate(m_width - br2, 0.0, 0.0);
    mm.rotate_ay(180.0 + m_angle);
    mm.translate(m_position.v1, 0.0, m_position.v2);


    return mm;
}


