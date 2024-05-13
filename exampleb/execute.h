//
// execute.h
//

#ifndef _EXECUTE_H_
#define _EXECUTE_H_

#include "queue.h"
#include "score.h"

#define SOLENOID_ID_NONE               0
#define SOLENOID_ID_OUT_HOLE           1
#define SOLENOID_ID_KNOCKER            2
#define SOLENOID_ID_TENS_CHIME         3
#define SOLENOID_ID_HUNDREDS_CHIME     4
#define SOLENOID_ID_THOUSANDS_CHIME    5
#define SOLENOID_ID_DROP_TARGET_JACKS  6
#define SOLENOID_ID_DROP_TARGET_QUEENS 7
#define SOLENOID_ID_DROP_TARGET_KINGS  8
#define SOLENOID_ID_DROP_TARGET_ACES   9
#define SOLENOID_ID_DROP_TARGET_ALL    10

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
