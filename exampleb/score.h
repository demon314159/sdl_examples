//
// score.h
//

#ifndef _SCORE_H_
#define _SCORE_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_PLAYERS 4
#define SCORE_DIGITS 6
#define TOTAL_DIGITS (MAX_PLAYERS * SCORE_DIGITS)


class Score
{
public:
    Score(float texture_id);
    ~Score();

    CadModel model(float animation_id) const;
    void advance(float seconds);
    int digits() const;
    float* data() const;

    void clear();
    void add_tens(int player, int n);
    void add_hundreds(int player, int n);
    void add_thousands(int player, int n);


private:
    float m_texture_id;
    int m_digit[TOTAL_DIGITS];
    float* m_data;
};

#endif // _SCORE_H_
