//
// dock.h
//

#ifndef _DOCK_H_
#define _DOCK_H_

class Dock
{
public:
    Dock(float pitch);
    ~Dock();

    float posx(int dock_id) const;
    float posz(int dock_id) const;

protected:
    float m_pitch;
};

#endif // _DOCK_H_
