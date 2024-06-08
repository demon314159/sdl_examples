//
// scoreboard_camera.cpp
//

#include "scoreboard_camera.h"
#include "bounding_box.h"
#include "pi.h"

#include <math.h>

ScoreboardCamera::ScoreboardCamera(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation)
    : m_width(width)
    , m_height(height)
    , m_initial_mag(initial_mag)
    , m_initial_offset(initial_offset)
    , m_initial_rotation(initial_rotation)
    , m_mag(initial_mag)
    , m_fov(45.0)
    , m_camz(0.0)
    , m_offset(initial_offset)
    , m_model_radius(1.0)
    , m_model_center({0.0, 0.0, 0.0})
    , m_projection()
    , m_mvp_matrix()
    , m_rot_matrix()
{
}

ScoreboardCamera::~ScoreboardCamera()
{
}

int ScoreboardCamera::width() const
{
    return m_width;
}

int ScoreboardCamera::height() const
{
    return m_height;
}

void ScoreboardCamera::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    update_matrices();
}

void ScoreboardCamera::frame(const CadModel* model)
{
    BoundingBox bb = model->bounding_box();
    float dx = (bb.vmax.v1 - bb.vmin.v1) / 2.0;
    float dy = (bb.vmax.v2 - bb.vmin.v2) / 2.0;
    float dz = (bb.vmax.v3 - bb.vmin.v3) / 2.0;
    m_model_radius = sqrt(dx*dx + dy*dy + dz*dz);
    m_model_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_model_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_model_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
    float q = tan(m_fov * (PI / 180.0) / 2.0);
    m_camz = m_model_radius / q;
    m_camz -= m_model_radius;
    update_matrices();
}

void ScoreboardCamera::zoom_home()
{
    m_mag = m_initial_mag;
    update_matrices();
}

void ScoreboardCamera::zoom(float factor)
{
    m_mag *= factor;
    update_matrices();
}

void ScoreboardCamera::translate_home()
{
    m_offset = m_initial_offset;
    update_matrices();
}

void ScoreboardCamera::translate_x(int pixels)
{
    // convert int pixels to float dx
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    float wx = aspect * (m_camz + m_model_radius) * q;
    float ratio = (float) pixels / fmax(1.0, (float) m_width);
    float dx = wx * ratio;
    m_offset.v1 += dx;
    update_matrices();
}

void ScoreboardCamera::translate_y(int pixels)
{
    // convert int pixels to float dy
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wy = (m_camz + m_model_radius) * q;
    float ratio = (float) pixels / fmax(1.0, (float) m_height);
    float dy = -wy * ratio;
    m_offset.v2 += dy;
    update_matrices();
}

void ScoreboardCamera::update_matrices()
{
    float znear = 0.1;
    float zfar = m_camz + 2.0 * m_model_radius;
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    m_projection.perspective(m_fov / m_mag, aspect, znear, zfar);

    Matrix4x4 matrix;
    matrix.unity();
    matrix.translate(m_offset.v1, m_offset.v2, -m_camz - m_model_radius);
    matrix.translate(-m_model_center.v1, -m_model_center.v2, -m_model_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
}

const float* ScoreboardCamera::mvp_data() const
{
    return m_mvp_matrix.data();
}

const float* ScoreboardCamera::rot_data() const
{
    return m_rot_matrix.data();
}

