//
// pyramid_lane_guide.h
//

#ifndef _PYRAMID_LANE_GUIDE_H_
#define _PYRAMID_LANE_GUIDE_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"

class PyramidLaneGuide
{
public:
    PyramidLaneGuide(float angle, Float3 position, float length, float height, float width, const PaintCan& color, float reflectivity, int steps);
    ~PyramidLaneGuide();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    float height() const;
    float width() const;
    void collide(Ball* ball) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_height;
    float m_width;
    PaintCan m_color;
    int m_steps;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _PYRAMID_LANE_GUIDE_H_
