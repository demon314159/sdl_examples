//
// switch.cpp
//

#include "switch.h"

#include <stdio.h>

Switch::Switch()
    : m_switches(0)
{
}

Switch::~Switch()
{
}

void Switch::sample(int switch_id, bool v)
{
    if (v) {
        printf("Switch::sample(%d, %d)\n", switch_id, v ? 1 : 0);
    }
}

int Switch::switches() const
{
    return m_switches;
}

bool Switch::state(int ix) const
{
    return false;
}

void Switch::add()
{
}

