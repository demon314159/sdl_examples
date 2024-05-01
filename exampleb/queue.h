//
// queue.h
//

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_ENTRIES 100

#define QCOMMAND_NOP             0
#define QCOMMAND_CLEAR_DIGITS    1
#define QCOMMAND_INCREMENT_DIGIT 2
#define QCOMMAND_OUT_HOLE_SOUND  3
#define QCOMMAND_OUT_HOLE        4

class Queue
{
public:
    Queue();
    ~Queue();

    void add_action(int command, int digit, int solenoid_id, float post_delay);
    bool empty() const;
    bool full() const;
    int action_command() const;
    int action_digit() const;
    int action_solenoid_id() const;
    float action_post_delay() const;
    void next_action();

private:
    int m_put_ix;
    int m_get_ix;
    int m_command[MAX_ENTRIES];
    int m_digit[MAX_ENTRIES];
    int m_solenoid_id[MAX_ENTRIES];
    float m_post_delay[MAX_ENTRIES];
    int next_put_ix() const;
    int next_get_ix() const;
};

#endif // _QUEUE_H_
