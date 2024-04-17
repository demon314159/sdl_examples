//
// queue.cpp
//

#include "queue.h"

Queue::Queue()
    : m_put_ix(0)
    , m_get_ix(0)
{
    for (int i = 0; i < MAX_ENTRIES; i++) {
        m_digit[i] = 0;
        m_sound_id[i] = 0;
        m_delay[i] = 0.0;
    }
}

Queue::~Queue()
{
}

void Queue::add_action(int digit, int sound_id, float delay)
{
    if (!full()) {
        m_digit[m_put_ix] = digit;
        m_sound_id[m_put_ix] = sound_id;
        m_delay[m_put_ix] = delay;
        m_put_ix = next_put_ix();
    }
}

bool Queue::empty() const
{
    return m_put_ix == m_get_ix;
}

bool Queue::full() const
{
    return next_put_ix() == m_get_ix;
}

int Queue::action_digit() const
{
    return m_digit[m_get_ix];
}

int Queue::action_sound_id() const
{
    return m_sound_id[m_get_ix];
}

float Queue::action_delay() const
{
    return m_delay[m_get_ix];
}

void Queue::next_action()
{
    if (!empty()) {
        m_get_ix = next_get_ix();
    }
}

int Queue::next_put_ix() const
{
    return (m_put_ix < (MAX_ENTRIES - 1)) ? m_put_ix + 1 : 0;
}

int Queue::next_get_ix() const
{
    return (m_get_ix < (MAX_ENTRIES - 1)) ? m_get_ix + 1 : 0;
}

