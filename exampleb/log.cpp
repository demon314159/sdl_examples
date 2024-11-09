//
// log.cpp
//

#include "log.h"
#include <stdio.h>
#include <math.h>

Log::Log()
    : m_guard_count(0)
    , m_frame_count(0)
{
    for (int i = 0; i < HIST_BINS; i++) {
        m_hist[i] = 0;
    }
}

Log::~Log()
{
    printf("Histogram of render times\n");
    printf("    %d Frames\n", m_frame_count);
    printf("    %d Guard Frames\n", GUARD_FRAMES);
    for (int i = 0; i < HIST_BINS; i++) {
        if (i == (HIST_BINS - 1)) {
            printf("        %2d ms and more: %d\n", i, m_hist[i]);
        } else {
            printf("        %2d ms to %2d ms: %d\n", i, i + 1, m_hist[i]);
        }
    }
}

void Log::render(int nanoseconds)
{
    ++m_frame_count;
    if (m_guard_count < GUARD_FRAMES) {
        ++m_guard_count;
    } else {
        add_sample(nanoseconds);
    }
}

void Log::add_sample(int nanoseconds)
{
    int t = nanoseconds / 1000000;
    if (t < 0) {
         t = 0;
    }
    if (t > (HIST_BINS - 1)) {
        t = HIST_BINS - 1;
    }
    ++m_hist[t];
}
