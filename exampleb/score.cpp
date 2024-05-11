//
// score.cpp
//

#include "score.h"

Score::Score(Scoreboard* scoreboard)
    : m_scoreboard(scoreboard)
    , m_fields(2 + m_scoreboard->max_players())
    , m_field(new Field[m_fields])
{
    int pd = m_scoreboard->player_digits();
    int mp = m_scoreboard->max_players();
    m_field[0] = {12, false, false, false, 4 * pd, 4 * pd + 1};
    m_field[1] = {70, false, false, true, 4 * pd + 2, 4 * pd + 3};
    for (int i = 0; i < mp; i++) {
        m_field[i + 2] = {0, false, false, false, i * pd, (i + 1) * pd - 1};
    }
    for (int i = 0; i < m_fields; i++) {
        apply_field(i);
    }
}

Score::~Score()
{
    delete [] m_field;
}

void Score::apply_field(int ix)
{
    Field f = m_field[ix];
    for (int i = f.first_digit; i <= f.last_digit; i++) {
        if (i == f.last_digit) {
            m_scoreboard->set_digit(i, {0, f.flash, f.blank});
        } else {
            m_scoreboard->set_digit(i, {f.leading_zeroes ? 0 : 10, f.flash, f.blank});
        }
    }
    int pos = f.last_digit;
    while (f.value > 0 && pos >= f.first_digit) {
        int v = f.value % 10;
        f.value = f.value / 10;
        m_scoreboard->set_digit(pos, {v, f.flash, f.blank});
        pos--;
    }
}

