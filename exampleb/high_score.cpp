//
// high_score.cpp
//

#include "high_score.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

#define DEFAULT_HIGH_SCORE 500000

HighScore::HighScore()
{
    m_score = DEFAULT_HIGH_SCORE;
    FILE* ffi = fopen(HIGH_SCORE_FILE_NAME, "rb");
    if (ffi == NULL) {
        return;
    }
    fread(this, sizeof(HighScore), 1, ffi);
    fclose(ffi);
}

HighScore::~HighScore()
{
}

int HighScore::score() const
{
    return m_score;
}

void HighScore::set_high_score(int score)
{
    if (score > m_score) {
        m_score = score;
        FILE* ffo = fopen(HIGH_SCORE_FILE_NAME, "wb");
        if (ffo == NULL)
            return;
        fwrite(this, sizeof(HighScore), 1, ffo);
        fclose(ffo);
    }
}

