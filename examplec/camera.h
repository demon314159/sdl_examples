//
// camera.h
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix4x4.h"
#include "cad_model.h"
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

    void zoom_home();
    void zoom(float factor);
    void rotate_home();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void translate_home();
    void translate_x(int pixels);
    void translate_y(int pixels);

    const float* mvp_data() const;
    const float* rot_data() const;
    void add_pose(const Float2& offset, const Float2& rotation, float mag);
    int poses() const;
    void set_pose(int ix);
    MouseVector new_mouse_vector(int sx, int sy) const;

    void show() const;

private:
    int m_width;
    int m_height;
    Pose* m_pose;
    float m_mag;
    float m_fov;
    float m_camz;
    Float2 m_offset;
    Float2 m_rotation;
    float m_model_radius;
    Float3 m_model_center;
    Matrix4x4 m_projection;
    Matrix4x4 m_mvp_matrix;
    Matrix4x4 m_rot_matrix;

    void update_matrices();
};

#endif // _CAMERA_H_
