//
// high_score.h
//

#ifndef _HIGH_SCORE_H_
#define _HIGH_SCORE_H_

#define HIGH_SCORE_FILE_NAME ".high_score.dat"

class HighScore
{
public:
    HighScore();
    ~HighScore();

    int score() const;
    void set_high_score(int score);

private:
    int m_score;
};

#endif // _HIGH_SCORE_H_
