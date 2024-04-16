//
// target.h
//

#ifndef _TARGET_H_
#define _TARGET_H_

#include "cad_model.h"
#include "float3.h"
#include "paint_can.h"
#include "drop_target.h"
#include "ball.h"
#include "sensor.h"

#define MAX_TARGETS 15

class Target
{
public:
    Target(float height);
    ~Target();

    int targets() const;
    void add(DropTarget* t);

    CadModel model(float animation_id) const;
    void collide(Ball* ball, Sensor* sensor) const;
    bool dropped(int ix) const;
    void set_dropped(int ix, bool v);
    void toggle_dropped(int ix);
    float* data() const;

private:
    float m_height;
    int m_targets;
    DropTarget* m_target[MAX_TARGETS];
    float* m_data;
};

#endif // _TARGET_H_
