//
// execute.h
//

#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "queue.h"
#include "score.h"
#include "lamp.h"

class Execute
{
public:
    Execute(Queue* queue, Score* score, Lamp* lamp);
    ~Execute();

    int advance(float seconds);

private:
    Queue* m_queue;
    Score* m_score;
    Lamp* m_lamp;
    float m_timer;
};

#endif // _EXECUTE_H_
