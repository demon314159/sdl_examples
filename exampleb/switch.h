//
// switch.h
//

#ifndef _SWITCH_H_
#define _SWITCH_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"

#define MAX_SWITCHES 25

class Switch
{
public:
    Switch();
    ~Switch();
    static void set(int switch_id);
    static void clear();
    static bool state(int switch_id);

private:
    static bool m_v[MAX_SWITCHES];
};

#endif // _SWITCH_H_
