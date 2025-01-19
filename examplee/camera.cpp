//
// camera.cpp
//

#include "camera.h"
#include "bounding_box.h"
#include "pi.h"

#include <math.h>

#define MAX_POSES 10

Camera::Camera(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation)
    : m_time_left(0.0)
    , m_hide_position({0.0, 0.0, 0.0})
    , m_hide_velocity({0.0, 0.0, 0.0})
    , m_hidden(false)
    , m_width(width)
    , m_height(height)
    , m_pose(new Pose(MAX_POSES))
    , m_mag(initial_mag)
    , m_fov(45.0)
    , m_camz(0.0)
    , m_offset(initial_offset)
    , m_rotation(initial_rotation)
    , m_object_radius(1.0)
    , m_object_center({0.0, 0.0, 0.0})
    , m_fixed_projection()
    , m_projection()
    , m_fixed_matrix()
    , m_hide_fixed_matrix()
    , m_mvp_matrix()
    , m_rot_matrix()
{
    m_pose->add(initial_offset, initial_rotation, initial_mag);
}

Camera::~Camera()
{
    delete m_pose;
}

void Camera::reconstruct(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation)
{
    m_width = width;
    m_height = height;
    m_pose->set_pose(0, initial_offset, initial_rotation, initial_mag);
    m_mag = initial_mag;
    m_fov = 45.0;
    m_camz = 0.0;
    m_offset = initial_offset;
    m_rotation = initial_rotation;
    m_object_radius = 1.0;
    m_object_center = {0.0, 0.0, 0.0};
}

int Camera::width() const
{
    return m_width;
}

int Camera::height() const
{
    return m_height;
}

void Camera::resize(int width, int height)
{
    m_width = width;
    m_height = height;
    update_matrices();
}

void Camera::frame(const CadModel* model)
{
    BoundingBox bb = model->bounding_box();
    frame(bb);
}

void Camera::frame(const BoundingBox& bb)
{
    float dx = (bb.vmax.v1 - bb.vmin.v1) / 2.0;
    float dy = (bb.vmax.v2 - bb.vmin.v2) / 2.0;
    float dz = (bb.vmax.v3 - bb.vmin.v3) / 2.0;
    m_object_radius = sqrt(dx*dx + dy*dy + dz*dz);
    m_object_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_object_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_object_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
    float q = tan(m_fov * (PI / 180.0) / 2.0);
    m_camz = m_object_radius / q;
    m_camz -= m_object_radius;
    update_matrices();
}

void Camera::zoom_home()
{
    m_mag = m_pose->pose(0).mag;
    update_matrices();
}

void Camera::zoom(float factor)
{
    m_mag *= factor;
    update_matrices();
}

void Camera::rotate_home()
{
    m_rotation = m_pose->pose(0).rotation;
    update_matrices();
}

void Camera::rotate_ax(float degrees)
{
    m_rotation.v1 += degrees;
    update_matrices();
}

void Camera::rotate_ay(float degrees)
{
    m_rotation.v2 += degrees;
    update_matrices();
}

void Camera::translate_home()
{
    m_offset = m_pose->pose(0).offset;
    update_matrices();
}

void Camera::translate_x(int pixels)
{
    // convert int pixels to float dx
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    float wx = aspect * (m_camz + m_object_radius) * q;
    float ratio = (float) pixels / fmax(1.0, (float) m_width);
    float dx = wx * ratio;
    m_offset.v1 += dx;
    update_matrices();
}

void Camera::translate_y(int pixels)
{
    // convert int pixels to float dy
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wy = (m_camz + m_object_radius) * q;
    float ratio = (float) pixels / fmax(1.0, (float) m_height);
    float dy = -wy * ratio;
    m_offset.v2 += dy;
    update_matrices();
}

Float3 Camera::top_left() const
{
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    float dy = tan((m_fov / 2.0) * PI / 180.0);
    float dx = dy * aspect;
    return {-dx, dy, -1.0};
}

void Camera::update_matrices()
{
    float znear = 0.1;
    float zfar = m_camz + 2.0 * m_object_radius;
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    m_fixed_projection.perspective(m_fov, aspect, znear, 3.0);
    m_projection.perspective(m_fov / m_mag, aspect, znear, zfar);

    Matrix4x4 matrix;
    matrix.unity();
    float dy = tan((m_fov / 2.0) * PI / 180.0);
    float dx = dy * aspect;
    matrix.translate(-dx, dy, -1.0);
    m_fixed_matrix = m_fixed_projection * matrix;
    update_hide_fixed_matrix();

    matrix.unity();
    matrix.translate(m_offset.v1, m_offset.v2, -m_camz - m_object_radius);
    matrix.rotate_ax(m_rotation.v1);
    matrix.rotate_ay(m_rotation.v2);
    matrix.translate(-m_object_center.v1, -m_object_center.v2, -m_object_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
}

void Camera::update_hide_fixed_matrix()
{
    Float3 cp = current_hide_position(m_hide_position, m_hide_velocity, m_time_left);
    Matrix4x4 matrix;
    matrix.unity();
    float aspect = float(m_width) / float(m_height ? m_height : 1.0);
    float dy = tan((m_fov / 2.0) * PI / 180.0);
    float dx = dy * aspect;
    matrix.translate(-dx, dy, -1.0);
    matrix.translate(cp.v1, cp.v2, cp.v3);
    m_hide_fixed_matrix = m_fixed_projection * matrix;
}

void Camera::advance_hide_fixed(float seconds)
{
    if (m_time_left > seconds) {
        m_time_left -= seconds;
    } else {
        m_time_left = 0.0;
    }
}

Float3 Camera::current_hide_position(const Float3& p, const Float3& v, float tleft) const
{
    Float3 cp;
    cp.v1 = p.v1 - tleft * v.v1;
    cp.v2 = p.v2 - tleft * v.v2;
    cp.v3 = p.v3 - tleft * v.v3;
    return cp;
}

const float* Camera::fixed_data() const
{
    return m_fixed_matrix.data();
}

const float* Camera::hide_fixed_data() const
{
    return m_hide_fixed_matrix.data();
}

const float* Camera::mvp_data() const
{
    return m_mvp_matrix.data();
}

const float* Camera::rot_data() const
{
    return m_rot_matrix.data();
}

void Camera::show() const
{
    printf("Camera offset(%5.3f, %5.3f) rotation(%5.3f, %5.3f) mag(%5.3f)\n",
           m_offset.v1, m_offset.v2, m_rotation.v1, m_rotation.v2, m_mag);
}

void Camera::add_pose(const Float2& offset, const Float2& rotation, float mag)
{
    m_pose->add(offset, rotation, mag);
}

int Camera::poses() const
{
    return m_pose->poses();
}

void Camera::set_pose(int ix)
{
    if (ix >= m_pose->poses()) {
        ix = 0;
    }
    m_offset = m_pose->pose(ix).offset;
    m_rotation = m_pose->pose(ix).rotation;
    m_mag = m_pose->pose(ix).mag;
    update_matrices();
}

MouseVector Camera::new_mouse_vector(int sx, int sy) const
{
    double camy = m_camz * tan((PI / 180.0) * m_fov / (2 * m_mag));
    double k = 2 * camy / (double) m_height;
    float v1 = k * ((double) sx - ((double) m_width) / 2);
    float v2 = k * (-(double) sy + ((double) m_height) / 2);

    Float3 vector = {v1 / m_camz, v2 / m_camz, -1.0};

    Float3 origin = {0.0, 0.0, 0.0};
    MouseVector tmv(origin, vector);
    tmv.translate({-m_offset.v1, -m_offset.v2, m_camz + m_object_radius});
    tmv.rotate_ax(-m_rotation.v1);
    tmv.rotate_ay(-m_rotation.v2);
    tmv.translate(m_object_center);
    return tmv;
}

MouseVector Camera::new_fixed_mouse_vector(int sx, int sy) const
{
    double camy = tan((PI / 180.0) * m_fov / 2.0);
    double k = 2 * camy / (double) m_height;
    float v1 = k * ((double) sx - ((double) m_width) / 2);
    float v2 = k * (-(double) sy + ((double) m_height) / 2);
    Float3 vector = {v1, v2, -1.0};
    Float3 origin = {0.0, 0.0, 0.0};
    MouseVector tmv(origin, vector);
    return tmv;
}

void Camera::hide(float posx, float posy, float posz, float period)
{
    if (set_hide_position(posx, posy, posz, period)) {
        m_hidden = true;
        update_matrices();
    }
}

void Camera::unhide(float period)
{
    if (set_hide_position(0.0, 0.0, 0.0, period)) {
        m_hidden = false;
        update_matrices();
    }
}

bool Camera::set_hide_position(float posx, float posy, float posz, float period)
{
    if (m_time_left > 0.0) {
        return false;
    }
    if (period > 0.0) {
        m_hide_velocity = velocity({posx, posy, posz}, m_hide_position, period);
        m_time_left = period;
    }
    m_hide_position.v1 = posx;
    m_hide_position.v2 = posy;
    m_hide_position.v3 = posz;
    return true;
}

bool Camera::hidden() const
{
    return m_hidden;
}

Float3 Camera::velocity(const Float3& p1, const Float3& p0, float period) const
{
    Float3 v;
    v.v1 = (p1.v1 - p0.v1) / period;
    v.v2 = (p1.v2 - p0.v2) / period;
    v.v3 = (p1.v3 - p0.v3) / period;
    return v;
}

