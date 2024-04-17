//
// queue.h
//

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_ENTRIES 100

class Queue
{
public:
    Queue();
    ~Queue();

    void add_action(int digit, int sound_id, float delay);
    bool empty() const;
    bool full() const;
    int action_digit() const;
    int action_sound_id() const;
    float action_delay() const;
    void next_action();

private:
    int m_put_ix;
    int m_get_ix;
    int m_digit[MAX_ENTRIES];
    int m_sound_id[MAX_ENTRIES];
    float m_delay[MAX_ENTRIES];
    int next_put_ix() const;
    int next_get_ix() const;
};

#endif // _QUEUE_H_
