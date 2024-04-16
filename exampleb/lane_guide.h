//
// lane_guide.h
//

#ifndef _LANE_GUIDE_H_
#define _LANE_GUIDE_H_

#include "cad_model.h"
#include "float3.h"
#include "ball.h"
#include "convex_reflector.h"
#include "straight_reflector.h"
#include "sensor.h"

class LaneGuide
{
public:
    LaneGuide(float angle, Float3 position, float length, float height, float width,
              const PaintCan& color, const PaintCan& face_color,
              float reflectivity, int steps, int sensor_id, int sensor_side, bool no_hat = false);
    ~LaneGuide();

    CadModel model(float animation_id) const;
    float angle() const;
    Float3 position() const;
    float length() const;
    float height() const;
    float width() const;
    void collide(Ball* ball, Sensor* sensor) const;

private:
    float m_angle;
    Float3 m_position;
    float m_length;
    float m_height;
    float m_width;
    PaintCan m_color;
    PaintCan m_face_color;
    int m_steps;
    int m_sensor_id;
    int m_sensor_side;
    bool m_no_hat;
    ConvexReflector m_reflector1;
    ConvexReflector m_reflector2;
    StraightReflector m_reflector3;
    StraightReflector m_reflector4;
};

#endif // _LANE_GUIDE_H_
