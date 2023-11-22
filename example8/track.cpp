//
// track.cpp
//

#include <cmath>
#include "track.h"
#include "straight_section.h"
#include "curved_right_section.h"
#include "curved_left_section.h"

Track::Track(int cars)
    : m_cars(cars)
    , m_sections(0)
{
    if (cars > MAX_CARS) {
        m_cars = MAX_CARS;
    }
    double initial_angle = 90.0;
    double straight_rise = 1.0;
    double r = 6.0;
    add_section(new StraightSection(m_cars, 2.0 * r, {0.0, 0.0, 0.0, initial_angle}, straight_rise));
    add_section(new StraightSection(m_cars, 2.0 * r, m_section[m_sections-1]->end_anchor()));
    add_section(new StraightSection(m_cars, 2.0 * r, m_section[m_sections-1]->end_anchor(), -straight_rise));
    add_section(new CurvedLeftSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor()));
    add_section(new StraightSection(m_cars, r, m_section[m_sections-1]->end_anchor()));
    add_section(new CurvedLeftSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor(), -1.0));
    add_section(new StraightSection(m_cars, 2.0 * r, m_section[m_sections-1]->end_anchor()));
    add_section(new CurvedLeftSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor()));
    add_section(new StraightSection(m_cars, 4.0 * r, m_section[m_sections-1]->end_anchor()));
    add_section(new CurvedRightSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor()));
    add_section(new StraightSection(m_cars, 2.0 * r, m_section[m_sections-1]->end_anchor()));
    add_section(new CurvedRightSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor(), 1.0));
    add_section(new StraightSection(m_cars, r, m_section[m_sections-1]->end_anchor()));
    add_section(new CurvedRightSection(m_cars, r, 90.0, m_section[m_sections-1]->end_anchor()));
}

Track::~Track()
{
    for (int i = 0; i < m_sections; i++) {
        delete m_section[i];
    }
}

int Track::cars() const
{
    return m_cars;
}

void Track::advance(int nanoseconds)
{
    if (m_sections > 0) {
        for (int i = 0; i < m_cars; i++) {
            m_car[i].advance(nanoseconds, m_section, m_sections);
        }
    }
}

double Track::car_yaw(int car_id) const
{
    return m_car[car_id].yaw();
}

double Track::car_pitch(int car_id) const
{
    return m_car[car_id].pitch();
}

Double3 Track::car_position(int car_id) const
{
    return m_car[car_id].position();
}

void Track::add_section(Section* section)
{
    if (m_sections < MAX_SECTIONS) {
        m_section[m_sections++] = section;
    }
}

int Track::sections() const
{
    return m_sections;
}

Section* Track::section(int ix)
{
    return m_section[ix];
}

Car* Track::car(int ix)
{
    return &m_car[ix];
}

