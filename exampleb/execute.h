//
// execute.h
//

#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "queue.h"
#include "score.h"

class Execute
{
public:
    Execute(Queue* queue, Score* score);
    ~Execute();

    int advance(float seconds);

private:
    Queue* m_queue;
    Score* m_score;
    float m_timer;
};

#endif // _EXECUTE_H_
