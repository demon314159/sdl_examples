//
// plastic_guide.cpp
//

#include "plastic_guide.h"
#include "pi.h"
#include <math.h>

PlasticGuide::PlasticGuide(const Float2& image_size,
                           const Float2& image_p1, const Float2& image_p2, const Float2& image_p3,
                           const Float2& blank_p1, const Float2& blank_p2, const Float2& blank_p3)
    : m_image_size(image_size)
    , m_image_p1(image_p1)
    , m_image_p2(image_p2)
    , m_image_p3(image_p3)
    , m_blank_p1(blank_p1)
    , m_blank_p2(blank_p2)
    , m_blank_p3(blank_p3)
{
}

Float2 PlasticGuide::blank_size() const
{
    return m_image_size;
}

Float2 PlasticGuide::blank_position() const
{
    return {(m_blank_p1.v1 + m_blank_p2.v1 + m_blank_p3.v1) / 3.0f,
            (m_blank_p1.v2 + m_blank_p2.v2 + m_blank_p3.v2) / 3.0f};
}

float PlasticGuide::blank_angle() const
{
    return 0.0;
}

