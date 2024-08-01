//
// dock.h
//

#ifndef _DOCK_H_
#define _DOCK_H_

#define MAX_SLOTS 10

class Dock
{
public:
    Dock(float pitch);
    ~Dock();

    void clear();
    float posx(int dock_id) const;
    float posz(int dock_id) const;
    float pitch() const;
    void assign_slot(int piece_id);
    int dock_id(int piece_id) const;

protected:
    float m_pitch;
    float m_dock_id;
    int m_slot[MAX_SLOTS];
};

#endif // _DOCK_H_
