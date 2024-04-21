//
// backglass_guide.h
//

#ifndef _BACKGLASS_GUIDE_H_
#define _BACKGLASS_GUIDE_H_

#include "float3.h"

class BackglassGuide
{
public:
    BackglassGuide(const Float2& position, const Float2& size, const Float2& image_size);

    Float3 position(const Float2& relative_position) const;
    Float2 size(const Float2& relative_size) const;

protected:
    Float2 m_position;
    Float2 m_size;
    Float2 m_image_size;
};

#endif // _BACKGLASS_GUIDE_H_

