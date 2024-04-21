//
// backglass_guide.cpp
//

#include "backglass_guide.h"
#include <math.h>

BackglassGuide::BackglassGuide(const Float3& position, const Float2& size, const Float2& image_size)
    : m_position(position)
    , m_size(size)
    , m_image_size(image_size)
{
}

Float3 BackglassGuide::position(const Float2& relative_position) const
{
    float x = relative_position.v1 * m_size.v1 / m_image_size.v1;
    float y = relative_position.v2 * m_size.v2 / m_image_size.v2;
    return {x + m_position.v1, -y + m_position.v2 + m_size.v2 / 2.0f, m_position.v3 - 0.001f};
}

Float2 BackglassGuide::size(const Float2& relative_size) const
{
    float x = relative_size.v1 * m_size.v1 / m_image_size.v1;
    float y = relative_size.v2 * m_size.v2 / m_image_size.v2;
    return {x, y};
}


