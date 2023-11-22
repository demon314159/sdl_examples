//
// straight_section.cpp
//

#include "straight_section.h"
#include "straight_track_shape.h"
#include "pi.h"
#include "track_style.h"
#include <cmath>

StraightSection::StraightSection(int lanes, double length, Anchor start_anchor, double rise)
    : m_lanes(lanes)
    , m_rise(rise)
    , m_length(length)
    , m_start_anchor(start_anchor)
    , m_pro(rise)
{
    double sina = sin(start_anchor.a * PI / 180.0);
    double cosa = cos(start_anchor.a * PI / 180.0);
    m_end_anchor = {m_start_anchor.x - length * sina,
                    m_start_anchor.y + rise,
                    m_start_anchor.z - length * cosa,
                    m_start_anchor.a};
}

StraightSection::~StraightSection()
{
}

double StraightSection::total_distance(int lane) const
{
    (void) lane;
    return m_length;
}

double StraightSection::car_yaw(int lane, double distance) const
{
    (void) lane;
    (void) distance;
    return m_start_anchor.a;
}

double StraightSection::car_pitch(int lane, double distance) const
{
    return m_pro.pitch(distance, total_distance(lane));
}

Double3 StraightSection::car_position(int lane, double distance) const
{
    double sina = sin(m_start_anchor.a * PI / 180.0);
    double cosa = cos(m_start_anchor.a * PI / 180.0);

    double dimx = 2.0 * TrackStyle::car_shoulder
               + (float) m_lanes * TrackStyle::car_width
               + (float) (m_lanes - 1) * TrackStyle::car_gap;

    double x0 = -dimx / 2.0;
    double x2 = x0 + TrackStyle::car_shoulder + TrackStyle::car_width / 2.0;
    double xc = x2 + ((double) lane) * (TrackStyle::car_width + TrackStyle::car_gap);
    double zc = - distance;
    double rot_xc = cosa * xc + sina * zc;
    double rot_zc = -sina * xc + cosa * zc;
    double ty = m_start_anchor.y + m_pro.height(distance, total_distance(lane));

    return {m_start_anchor.x + rot_xc, ty, m_start_anchor.z + rot_zc};
}

Anchor StraightSection::start_anchor() const
{
    return m_start_anchor;
}

Anchor StraightSection::end_anchor() const
{
    return m_end_anchor;
}

CadModel StraightSection::cad_model() const
{
    CadModel cm;
    CadModel s = CadModel(StraightTrackShape(m_lanes, m_length, m_rise));
    s.rotate_ay(m_start_anchor.a);
    cm.add(s, m_start_anchor.x, m_start_anchor.y, m_start_anchor.z);
    return cm;
}
