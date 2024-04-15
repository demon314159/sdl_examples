//
// switch.cpp
//

#include "switch.h"

bool Switch::m_v[MAX_SWITCHES];

Switch::Switch()
{
}

Switch::~Switch()
{
}

void Switch::set(int switch_id)
{
    m_v[switch_id] = true;
}

bool Switch::state(int switch_id)
{
    return m_v[switch_id];
}

void Switch::clear()
{
    for (int i = 0; i < MAX_SWITCHES; i++) {
        m_v[i] = false;
    }
}


