//
// hover.h
//

#ifndef _HOVER_H_
#define _HOVER_H_

#include "float3.h"

class Hover
{
public:
    Hover();
    ~Hover();
    bool on() const;
    int piece_id() const;
    Float3 offset() const;
    void start(int piece_id, float offsetx, float offsety, float offsetz);
    void stop();

protected:
    bool m_on;
    int m_piece_id;
    Float3 m_offset;
};

#endif // _HOVER_H_
