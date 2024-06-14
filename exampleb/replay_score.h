//
// replay_score.h
//

#ifndef _REPLAY_SCORE_H_
#define _REPLAY_SCORE_H_

#include "score.h"

class ReplayScore
{
public:
    ReplayScore(int max_players, int score1, int score2, int score3);
    ~ReplayScore();

    void reset();
    bool check(const Score* score);

private:
    int m_max_players;
    int m_score1;
    int m_score2;
    int m_score3;
    int* m_latest_score;
    int* m_last_latest_score;

    bool check_one(int replay_score, int latest_score, int last_latest_score) const;
};

#endif // _REPLAY_SCORE_H_
