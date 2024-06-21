//
// pose.h
//

#ifndef _POSE_H_
#define _POSE_H_

#include "float3.h"

struct PoseRec {
  Float2 offset;
  Float2 rotation;
  float mag;
};

class Pose
{
public:
    Pose(int max_poses);
    ~Pose();

    int poses() const;
    void add(const Float2& offset, const Float2& rotation, float mag);
    PoseRec pose(int ix) const;
    void set_pose(int ix, const Float2& offset, const Float2& rotation, float mag);

private:
    int m_max_poses;
    int m_poses;
    PoseRec* m_pose;
};

#endif // _POSE_H_
