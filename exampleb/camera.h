//
// camera.h
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix4x4.h"
#include "float3.h"

class Camera
{
public:
    Camera();
    ~Camera();

    int height() const;
    int width() const;

    void resize(int width, int height);
    void set_target_position(float target_radius, Float3 target_center);

    void zoom_home();
    void zoom(float factor);
    void rotate_home();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void translate_home();
    void translate_x(float dx);
    void translate_y(float dy);


    const float* mvp_data() const;
    const float* rot_data() const;

private:
    int m_width;
    int m_height;
    float m_mag;
    float m_fovy;
    float m_aspect;
    float m_near;
    float m_far;
    float m_camz;
    Float2 m_offset;
    Float2 m_rotation;
    float m_target_radius;
    Float3 m_target_center;



    Matrix4x4 m_mvp_matrix;
    Matrix4x4 m_rot_matrix;
};

#endif // _CAMERA_H_
