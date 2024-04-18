//
// queue.cpp
//

#include "queue.h"

Queue::Queue()
    : m_put_ix(0)
    , m_get_ix(0)
{
    for (int i = 0; i < MAX_ENTRIES; i++) {
        m_command[i] = 0;
        m_digit[i] = 0;
        m_solenoid_id[i] = 0;
        m_post_delay[i] = 0.0;
    }
}

Queue::~Queue()
{
}

void Queue::add_action(int command, int digit, int solenoid_id, float post_delay)
{
    if (!full()) {
        m_command[m_put_ix] = command;
        m_digit[m_put_ix] = digit;
        m_solenoid_id[m_put_ix] = solenoid_id;
        m_post_delay[m_put_ix] = post_delay;
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

int Queue::action_command() const
{
    return m_command[m_get_ix];
}

int Queue::action_digit() const
{
    return m_digit[m_get_ix];
}

int Queue::action_solenoid_id() const
{
    return m_solenoid_id[m_get_ix];
}

float Queue::action_post_delay() const
{
    return m_post_delay[m_get_ix];
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

