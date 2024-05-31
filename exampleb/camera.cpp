//
// camera.cpp
//

#include "camera.h"


#define INITIAL_MAG  2.625

Camera::Camera()
    : m_width(1920)
    , m_height(1080)
    , m_mvp_matrix()
    , m_rot_matrix()

{
}

Camera::~Camera()
{
}

int Camera::width() const
{
    return m_width;
}

int Camera::height() const
{
    return m_height;
}

const float* Camera::mvp_data() const
{
    return m_mvp_matrix.data();
}

const float* Camera::rot_data() const
{
    return m_rot_matrix.data();
}

