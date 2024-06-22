//
// pose.cpp
//

#include "pose.h"

Pose::Pose(int max_poses)
    : m_max_poses(max_poses)
    , m_poses(0)
    , m_pose(new PoseRec[max_poses])
{

}

Pose::~Pose()
{
    delete [] m_pose;
}

int Pose::poses() const
{
    return m_poses;
}

void Pose::add(const Float2& offset, const Float2& rotation, float mag)
{
   if (m_poses < m_max_poses) {
       m_pose[m_poses] = {offset, rotation, mag};
       ++m_poses;
   }
}

PoseRec Pose::pose(int ix) const
{
    if (ix >= m_max_poses) {
        ix = 0;
    }
    return m_pose[ix];
}

void Pose::set_pose(int ix, const Float2& offset, const Float2& rotation, float mag)
{
    if (ix >= m_max_poses) {
        ix = 0;
    }
    m_pose[ix].offset = offset;
    m_pose[ix].rotation = rotation;
    m_pose[ix].mag = mag;
}
