//
// camera.h
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix4x4.h"
#include "cad_model.h"
#include "bounding_box.h"
#include "pose.h"
#include "float3.h"
#include "mouse_vector.h"

#include <stdio.h>

class Camera
{
public:
    Camera(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation);
    ~Camera();
    void reconstruct(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation);

    int height() const;
    int width() const;

    void resize(int width, int height);
    void frame(const CadModel* model);
    void frame(const BoundingBox& bb);

    void zoom_home();
    void zoom(float factor);
    void rotate_home();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void translate_home();
    void translate_x(int pixels);
    void translate_y(int pixels);

    const float* fixed_left_data() const;
    const float* fixed_right_data() const;
    const float* hide_left_data() const;
    const float* hide_right_data() const;
    const float* mvp_data() const;
    const float* rot_data() const;
    void add_pose(const Float2& offset, const Float2& rotation, float mag);
    int poses() const;
    void set_pose(int ix);
    void hide_left(float posx, float posy, float posz, float period = 0.0);
    void unhide_left(float period = 0.0);
    bool hidden_left() const;
    void hide_right(float posx, float posy, float posz, float period = 0.0);
    void unhide_right(float period = 0.0);
    bool hidden_right() const;

    MouseVector new_fixed_mouse_vector(int sx, int sy) const;
    MouseVector new_mouse_vector(int sx, int sy) const;
    void advance_hide(float seconds);
    void update_hide_matrix();
    Float3 top_left() const;
    Float3 top_right() const;

    void show() const;

private:
    float m_left_time_left;
    Float3 m_hide_left_position;
    Float3 m_hide_left_velocity;
    bool m_hidden_left;
    float m_right_time_left;
    Float3 m_hide_right_position;
    Float3 m_hide_right_velocity;
    bool m_hidden_right;
    int m_width;
    int m_height;
    Pose* m_pose;
    float m_mag;
    float m_fov;
    float m_camz;
    Float2 m_offset;
    Float2 m_rotation;
    float m_object_radius;
    Float3 m_object_center;
    Matrix4x4 m_fixed_projection;
    Matrix4x4 m_projection;
    Matrix4x4 m_fixed_left_matrix;
    Matrix4x4 m_fixed_right_matrix;
    Matrix4x4 m_hide_left_matrix;
    Matrix4x4 m_hide_right_matrix;
    Matrix4x4 m_mvp_matrix;
    Matrix4x4 m_rot_matrix;

    void update_matrices();
    bool set_hide_left_position(float posx, float posy, float posz, float period);
    bool set_hide_right_position(float posx, float posy, float posz, float period);
    Float3 velocity(const Float3& p1, const Float3& p0, float period) const;
    Float3 current_hide_position(const Float3& p, const Float3& v, float tleft) const;
};

#endif // _CAMERA_H_
