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
    static void sample(int switch_id, bool v);

    int switches() const;
    void add();

    bool state(int ix) const;

private:
    int m_switches;
};

#endif // _SWITCH_H_
