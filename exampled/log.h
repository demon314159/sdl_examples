//
// log.h
//

#ifndef _LOG_H_
#define _LOG_H_

#define HIST_BINS 30
#define GUARD_FRAMES 100

class Log
{
public:
    Log();
    ~Log();

    void render(int nanoseconds);

private:
    int m_guard_count;
    int m_frame_count;
    int m_hist[HIST_BINS];

    void add_sample(int nanoseconds);
};

#endif // _LOG_H_
