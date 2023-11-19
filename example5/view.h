
#ifndef _VIEW_H_
#define _VIEW_H_

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>
#include <stdio.h>

class View
{
public:
    View();
    ~View();
    void initialize();
    void render();

private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_GLContext m_context;
    GLint m_pos_attr;
    GLint m_col_attr;
    GLint m_matrix_uniform;
    GLuint m_program;
    unsigned int m_vao;
    unsigned int m_vbo;
    int m_frame = 0;

    bool add_shader_from_source_file(GLuint shader, const char* name);
    void perspective(float fovy, float aspect, float near, float far);

    void print_program_log(GLuint program);
    void print_shader_log(GLuint shader);

};

#endif // _VIEW_H_
