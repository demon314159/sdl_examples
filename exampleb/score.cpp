//
// score.cpp
//

#include "score.h"
#include "plane_shape.h"

Score::Score(float texture_id)
    : m_texture_id(texture_id)
    , m_data(new float[TOTAL_DIGITS])
{
    clear();
}

Score::~Score()
{
    delete [] m_data;
}

void Score::clear()
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        m_digit[i] = 0;
    }
}

void Score::advance(float seconds)
{
}

int Score::digits() const
{
    return TOTAL_DIGITS;
}

CadModel Score::model(float animation_id) const
{
    float k = 0.8;
    float w = 0.040 * k;
    float h = 0.069 * k;
    CadModel mm;
    for (int j = 0; j < MAX_PLAYERS; j++) {
        for (int i = 0; i < SCORE_DIGITS; i++) {
            CadModel score(PlaneShape(w, h, m_texture_id, {0.0, 0.0}, {0.1, 1.0}), PaintCan(1.0, 1.0, 1.0), animation_id + (float) i);
            mm.add(score, w * (float) i, 0.020, h * 1.2 *(float) j);
        }
    }
    mm.rotate_ax(90.0 - 40.0);
    mm.translate(-0.2, 0.05, 0.2);
    return mm;
}

float* Score::data() const
{
    for (int i = 0; i < TOTAL_DIGITS; i++) {
        m_data[i] = 0.1 * (float) m_digit[i];
    }
    return m_data;
}
