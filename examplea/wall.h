//
// wall.h
//

#ifndef _WALL_H_
#define _WALL_H_

#include "float3.h"
#include "ball.h"
#include "cad_model.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class Wall
{
public:
    Wall(float angle, Float3 position, float length, float radius, float height,
         float bumper_thickness, float bumper_height,
         const PaintCan& body_color, const PaintCan& bumper_color,
         float reflectivity, int steps);

    ~Wall();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    void collide(Ball& ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_radius;
    float m_height;
    float m_bumper_thickness;
    float m_bumper_height;
    PaintCan m_body_color;
    PaintCan m_bumper_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _WALL_H_
