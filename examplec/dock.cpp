//
// dock.cpp
//

#include "dock.h"

Dock::Dock(float pitch)
    : m_pitch(pitch)
{
}

Dock::~Dock()
{
}

float Dock::posx(int dock_id) const
{
    switch(dock_id) {
        case 0:
            return 1.0 * m_pitch;
        case 1:
            return 8.0 * m_pitch;
        case 2:
            return 1.0 * m_pitch;
        case 3:
            return 8.0 * m_pitch;
        case 4:
            return -5.0 * m_pitch;
        case 5:
            return 14.0 * m_pitch;
        case 6:
            return -5.0 * m_pitch;
        case 7:
            return 14.0 * m_pitch;
        case 8:
            return -5.0 * m_pitch;
        case 9:
            return 14.0 * m_pitch;
    };
    return 0.0;
}

float Dock::posz(int dock_id) const
{
    switch(dock_id) {
        case 0:
            return -9.0 * m_pitch;
        case 1:
            return -9.0 * m_pitch;
        case 2:
            return 4.0 * m_pitch;
        case 3:
            return 4.0 * m_pitch;
        case 4:
            return -2.5 * m_pitch;
        case 5:
            return -2.5 * m_pitch;
        case 6:
            return -9.0 * m_pitch;
        case 7:
            return -9.0 * m_pitch;
        case 8:
            return 4.0 * m_pitch;
        case 9:
            return 4.0 * m_pitch;
    };
    return 0.0;
}
