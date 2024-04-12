//
// plastic_guide.cpp
//

#include "plastic_guide.h"
#include "pi.h"
#include <math.h>

#include <stdio.h>

PlasticGuide::PlasticGuide(const Float2& image_size,
                           const Float2& image_p1, const Float2& image_p2, const Float2& image_p3,
                           const Float2& blank_p1, const Float2& blank_p2, const Float2& blank_p3)
    : m_blank_size({0.0, 0.0})
    , m_blank_position({0.0, 0.0})
    , m_blank_angle(0.0)
{
    float ia1 = angle(image_p1, image_p2);
    float ia2 = angle(image_p2, image_p3);
    float ia3 = angle(image_p3, image_p1);
    float ba1 = angle(blank_p1, blank_p2);
    float ba2 = angle(blank_p2, blank_p3);
    float ba3 = angle(blank_p3, blank_p1);
    float da1 = ia1 - ba1;
    float da2 = ia2 - ba2;
    float da3 = ia3 - ba3;
    m_blank_angle = (da1 + da2 + da3) / 3.0;

    float il1 = length(image_p1, image_p2);
    float il2 = length(image_p2, image_p3);
    float il3 = length(image_p3, image_p1);
    float bl1 = length(blank_p1, blank_p2);
    float bl2 = length(blank_p2, blank_p3);
    float bl3 = length(blank_p3, blank_p1);
    float k1 = bl1 / il1;
    float k2 = bl2 / il2;
    float k3 = bl3 / il3;
    float kavg = (k1 + k2 + k3) / 3.0f;
    m_blank_size = {image_size.v1 * kavg, image_size.v2 * kavg};

    Float2 blank_position = position(blank_p1, blank_p2, blank_p3);
    Float2 image_position = position(image_p1, image_p2, image_p3);
    image_position.v1 -= (image_size.v1 / 2.0f);
    image_position.v2 -= (image_size.v2 / 2.0f);
    image_position.v1 = kavg * image_position.v1;
    image_position.v2 = kavg * image_position.v2;
    image_position = rotated(image_position, m_blank_angle);
    m_blank_position = {blank_position.v1 - image_position.v1, blank_position.v2 - image_position.v2};
}

PlasticGuide::PlasticGuide(const Float2& image_size,
                           const Float2& image_p1, const Float2& image_p2,
                           const Float2& blank_p1, const Float2& blank_p2)
    : m_blank_size({0.0, 0.0})
    , m_blank_position({0.0, 0.0})
    , m_blank_angle(0.0)
{
    float ia1 = angle(image_p1, image_p2);
    float ba1 = angle(blank_p1, blank_p2);
    float da1 = ia1 - ba1;
    m_blank_angle = da1;

    float il1 = length(image_p1, image_p2);
    float bl1 = length(blank_p1, blank_p2);
    float k1 = bl1 / il1;
    float kavg = k1;
    m_blank_size = {image_size.v1 * kavg, image_size.v2 * kavg};

    Float2 blank_position = position(blank_p1, blank_p2);
    Float2 image_position = position(image_p1, image_p2);
    image_position.v1 -= (image_size.v1 / 2.0f);
    image_position.v2 -= (image_size.v2 / 2.0f);
    image_position.v1 = kavg * image_position.v1;
    image_position.v2 = kavg * image_position.v2;
    image_position = rotated(image_position, m_blank_angle);
    m_blank_position = {blank_position.v1 - image_position.v1, blank_position.v2 - image_position.v2};
}

Float2 PlasticGuide::blank_size() const
{
    return m_blank_size;
}

Float2 PlasticGuide::blank_position() const
{
    return m_blank_position;
}

float PlasticGuide::blank_angle() const
{
    return m_blank_angle;
}

float PlasticGuide::angle(const Float2& p1, const Float2& p2) const
{
    return atan2(p2.v2 - p1.v2, p2.v1 - p1.v1) * 180.0 / PI;
}

float PlasticGuide::length(const Float2& p1, const Float2& p2) const
{
    double dx = p2.v1 - p1.v1;
    double dy = p2.v2 - p1.v2;
    return sqrt(dx * dx + dy * dy);
}

Float2 PlasticGuide::position(const Float2& p1, const Float2& p2, const Float2& p3) const
{
    return {(p1.v1 + p2.v1 + p3.v1) / 3.0f, (p1.v2 + p2.v2 + p3.v2) / 3.0f};
}

Float2 PlasticGuide::position(const Float2& p1, const Float2& p2) const
{
    return {(p1.v1 + p2.v1) / 2.0f, (p1.v2 + p2.v2) / 2.0f};
}

Float2 PlasticGuide::rotated(Float2 point, float angle) const
{
    float cost = cos(angle * PI / 180.0);
    float sint = sin(angle * PI / 180.0);

    float tx = cost * point.v1 + sint * point.v2;
    float tz = -sint * point.v1 + cost * point.v2;
    return {tx, tz};
}

