//
// camera.h
//

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "matrix4x4.h"
#include "cad_model.h"
#include "float3.h"

class Camera
{
public:
    Camera(int width, int height, float initial_mag, const Float2& initial_offset, const Float2& initial_rotation);
    ~Camera();

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
    const float* scoreboard_mvp_data() const;
    const float* scoreboard_rot_data() const;

private:
    int m_width;
    int m_height;
    float m_initial_mag;
    Float2 m_initial_offset;
    Float2 m_initial_rotation;
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
    Matrix4x4 m_scoreboard_mvp_matrix;
    Matrix4x4 m_scoreboard_rot_matrix;

    void update_matrices();
};

#endif // _CAMERA_H_
