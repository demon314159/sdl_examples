//
// execute.h
//

#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "queue.h"
#include "score.h"
#include "lamp.h"
#include "replay_score.h"
#include "gauge.h"

class Execute
{
public:
    Execute(Queue* queue, Queue* fast_queue, Score* score, Lamp* lamp, ReplayScore* replay_score, Gauge* gauge);
    ~Execute();

    int advance(float seconds);

private:
    Queue* m_queue;
    Queue* m_fast_queue;
    Score* m_score;
    Lamp* m_lamp;
    ReplayScore* m_replay_score;
    Gauge* m_gauge;
    int m_initial_high_game;
    float m_timer;

    int interpret(const QueueRec& qrec);
};

#endif // _EXECUTE_H_
