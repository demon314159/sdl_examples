//
// view.h
//

#ifndef _VIEW_H_
#define _VIEW_H_

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <stdio.h>

#include "vertex_data.h"
#include "matrix4x4.h"
#include "toy.h"
#include "cad_model.h"

#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH ((INITIAL_HEIGHT * 1920) / 1080)
#define INITIAL_XROT 40.0
#define INITIAL_MAG 2.25

class View
{
public:
    View(SDL_Window* window);
    virtual ~View();
    void initialize();
    void resize(int w, int h);
    void render();
    void rotate_ax(float degrees);
    void rotate_ay(float degrees);
    void rotate_home();
    void zoom(float factor);
    void zoom_home();
    void translate_x(int x);
    void translate_y(int y);
    void translate_home();
    void set_mag(float mag);
    int width() const;
    int height() const;

protected:
    bool init_shaders();
    void resize_calc();
    void position_camera();
    void check_storage();
    void copy_vertices();
    void copy_facets();
    void sub_copy_facets(CadModel* model, VertexData* vertices, int& vix);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_GLContext m_context;
    GLuint m_program;
    GLint m_pos_attr;
    GLint m_col_attr;
    GLint m_norm_attr;
    GLint m_ani_attr;
    GLint m_mvp_matrix_uniform;
    GLint m_rot_matrix_uniform;
    GLint* m_animation_matrix_uniform;
    unsigned int m_vao;
    unsigned int m_vbo;
    int m_frame;
    int m_max_vertex_count;
    int m_facet_count;
    Toy* m_toy;
    float m_radius;
    Float3 m_center;
    int m_width;
    int m_height;
    float m_aspect;
    float m_mag;
    float m_fov;
    float m_camz;
    float m_xrot;
    float m_yrot;
    float m_xoff;
    float m_yoff;
    Matrix4x4 m_mvp_matrix;
    Matrix4x4 m_rot_matrix;
    Matrix4x4 m_projection;
    float m_last_count;

    bool add_shader_from_source_file(GLuint shader, const char* name);
    void print_program_log(GLuint program);
    void print_shader_log(GLuint shader);
};

#endif // _VIEW_H_
