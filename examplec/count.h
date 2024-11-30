//
// count.h
//

#ifndef _COUNT_H_
#define _COUNT_H_

#include "float3.h"
#include "cad_model.h"

class Count
{
public:
    Count(int digits, int initial_value, float width, float height, const Float2& position);
    ~Count();

    void set_value(int value);
    int digits() const;
    int count() const;

    CadModel model(float animation_id, float texture_id) const;
    const float* data();

private:
    int m_digits;
    int m_count;
    float m_width;
    float m_height;
    Float2 m_position;
    float* m_data;
};

#endif // _COUNT_H_

