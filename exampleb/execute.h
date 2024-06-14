//
// execute.h
//

#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "queue.h"
#include "score.h"
#include "lamp.h"
#include "replay_score.h"

class Execute
{
public:
    Execute(Queue* queue, Score* score, Lamp* lamp, ReplayScore* replay_score);
    ~Execute();

    int advance(float seconds);

private:
    Queue* m_queue;
    Score* m_score;
    Lamp* m_lamp;
    ReplayScore* m_replay_score;
    float m_timer;
};

#endif // _EXECUTE_H_
