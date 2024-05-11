//
// score.h
//

#ifndef _SCORE_H_
#define _SCORE_H_

#include "scoreboard.h"
#include "field.h"

class Score
{
public:
    Score(Scoreboard* scoreboard);
    ~Score();

private:
    Scoreboard* m_scoreboard;
    int m_fields;
    Field* m_field;
    void apply_field(int ix);
};

#endif // _SCORE_H_
