//
// queue.cpp
//

#include "queue.h"

Queue::Queue()
    : m_put_ix(0)
    , m_get_ix(0)
{
    for (int i = 0; i < MAX_ENTRIES; i++) {
        m_rec[i] = {QCOMMAND_NOP, 0, 0};
    }
}

Queue::~Queue()
{
}

bool Queue::empty() const
{
    return m_put_ix == m_get_ix;
}

bool Queue::full() const
{
    return next_put_ix() == m_get_ix;
}

void Queue::put(const QueueRec& rec)
{
    if (!full()) {
        m_rec[m_put_ix] = rec;
        m_put_ix = next_put_ix();
    }
}

void Queue::put(int command, int which_one, int value)
{
    QueueRec t = {command, which_one, value};
    if (!full()) {
        m_rec[m_put_ix] = t;
        m_put_ix = next_put_ix();
    }
}

QueueRec Queue::get()
{
    QueueRec t;
    if (empty()) {
        t = {QCOMMAND_NOP, 0, 0};
    } else {
        t = m_rec[m_get_ix];
        m_get_ix = next_get_ix();
    }
    return t;
}

int Queue::next_put_ix() const
{
    return (m_put_ix < (MAX_ENTRIES - 1)) ? m_put_ix + 1 : 0;
}

int Queue::next_get_ix() const
{
    return (m_get_ix < (MAX_ENTRIES - 1)) ? m_get_ix + 1 : 0;
}

