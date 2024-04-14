//
// target.cpp
//

#include "target.h"
#include <math.h>

Target::Target(float height)
    : m_height(height)
    , m_targets(0)
    , m_data(new float[MAX_TARGETS])
{
}

Target::~Target()
{
    for (int i = 0; i < m_targets; i++) {
        delete m_target[i];
    }
    delete m_data;
}

float* Target::data() const
{
    for (int i = 0; i < m_targets; i++) {
        m_data[i] = m_target[i]->dropped() ? 0.8f * m_height : 0.0;
    }
    return m_data;
}

int Target::targets() const
{
    return m_targets;
}

void Target::add(DropTarget* t)
{
    if (m_targets < MAX_TARGETS) {
        m_target[m_targets]= t;
    }
    ++m_targets;
}

CadModel Target::model() const
{
    CadModel cm;
    for (int i = 0; i < m_targets; i++) {
        cm.add(m_target[i]->model(200.0 + (float) i), 0.0, 0.0, 0.0);
    }
    return cm;
}

void Target::collide(Ball* ball) const
{
    for (int i = 0; i < m_targets; i++) {
        m_target[i]->collide(ball);
    }
}

bool Target::dropped(int ix) const
{
    return m_target[ix]->dropped();
}

void Target::set_dropped(int ix, bool v)
{
    m_target[ix]->set_dropped(v);
}

void Target::toggle_dropped(int ix)
{
    m_target[ix]->set_dropped(!m_target[ix]->dropped());
}

