//
// view.h
//

#ifndef _VIEW_H_
#define _VIEW_H_

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <chrono>

#include "vertex_data.h"
#include "toy.h"

class View
{
public:
    View(SDL_Window* window);
    virtual ~View();
    bool button(int code, bool shifted, bool on);
    bool mouse(SDL_Event* e, bool on);
    void initialize();
    void resize(int w, int h);
    void render();
    Camera* camera();

protected:
    bool init_shaders();
    void check_storage();
    void copy_vertices();
    void copy_facets();
    void sub_copy_facets(CadModel* model, VertexData* vertices, int& vix);

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_GLContext m_context;
    GLuint m_program;
    GLint m_position_attr;
    GLint m_color_attr;
    GLint m_normal_attr;
    GLint m_texture_position_attr;
    GLint m_animation_id_attr;
    GLint m_texture_id_attr;
    GLint m_mvp_matrix_uniform;
    GLint m_rot_matrix_uniform;
    unsigned int m_vao;
    unsigned int m_vbo;
    int m_frame;
    int m_max_vertex_count;
    int m_vertex_count;
    Toy* m_toy;

    std::chrono::high_resolution_clock::time_point m_last_time_point;
    bool add_shader_from_source_file(GLuint shader, const char* name);
    void print_program_log(GLuint program);
    void print_shader_log(GLuint shader);
    void generate_textures();
    void generate_texture(const char* fname);
};

#endif // _VIEW_H_
