//
// replay_score.cpp
//

#include "replay_score.h"

ReplayScore::ReplayScore(int max_players, int score1, int score2, int score3)
    : m_max_players(max_players)
    , m_score1(score1)
    , m_score2(score2)
    , m_score3(score3)
    , m_latest_score(new int[max_players])
    , m_last_latest_score(new int[max_players])
{
    reset();
}

ReplayScore::~ReplayScore()
{
    delete [] m_latest_score;
    delete [] m_last_latest_score;
}

void ReplayScore::reset()
{
    for (int i = 0; i < m_max_players; i++) {
        m_latest_score[i] = 0;
        m_last_latest_score[i] = 0;
    }
}

bool ReplayScore::check(const Score* score)
{
    bool replay_flag = false;

    for (int i = 0; i < m_max_players; i++) {
        m_latest_score[i] = score->get_player_score(i + 1);
        bool f1 = check_one(m_score1, m_latest_score[i], m_last_latest_score[i]);
        bool f2 = check_one(m_score2, m_latest_score[i], m_last_latest_score[i]);
        bool f3 = check_one(m_score3, m_latest_score[i], m_last_latest_score[i]);
        m_last_latest_score[i] = m_latest_score[i];
        if (f1 || f2 || f3) {
            replay_flag = true;
        }
    }
    return replay_flag;
}

bool ReplayScore::check_one(int replay_score, int latest_score, int last_latest_score) const
{
    return (latest_score >= replay_score) && (last_latest_score < replay_score);
}


