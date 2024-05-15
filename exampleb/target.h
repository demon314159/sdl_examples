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

#define DROP_TARGET_ID_10    0
#define DROP_TARGET_ID_J1    1
#define DROP_TARGET_ID_J2    2
#define DROP_TARGET_ID_Q1    3
#define DROP_TARGET_ID_Q2    4
#define DROP_TARGET_ID_Q3    5
#define DROP_TARGET_ID_K1    6
#define DROP_TARGET_ID_K2    7
#define DROP_TARGET_ID_K3    8
#define DROP_TARGET_ID_K4    9
#define DROP_TARGET_ID_A1    10
#define DROP_TARGET_ID_A2    11
#define DROP_TARGET_ID_JOKER 12
#define DROP_TARGET_ID_A3    13
#define DROP_TARGET_ID_A4    14


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
