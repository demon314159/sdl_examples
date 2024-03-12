//
// view.cpp
//

#include "view.h"
#include "matrix4x4.h"
#include "matrix3x3.h"
#include "paint_can.h"
#include "bounding_box.h"
#include "look.h"
#include "pi.h"
#include <math.h>
#include <sys/stat.h>
#include <algorithm>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define notVERBOSE

View::View(SDL_Window* window)
    : m_window(window)
    , m_renderer(nullptr)
    , m_context(nullptr)
    , m_program(0)
    , m_position_attr(0)
    , m_color_attr(0)
    , m_normal_attr(0)
    , m_texture_position_attr(0)
    , m_animation_id_attr(0)
    , m_texture_id_attr(0)
    , m_mvp_matrix_uniform(0)
    , m_rot_matrix_uniform(0)
    , m_animation_matrix_uniform(nullptr)
    , m_vao(0)
    , m_vbo(0)
    , m_texture(0)
    , m_frame(0)
    , m_max_vertex_count(1024 * 1024)
    , m_facet_count(0)
    , m_toy(new Toy())
    , m_radius(2.0)
    , m_center({0.0, 0.0, 0.0})
    , m_width(INITIAL_WIDTH)
    , m_height(INITIAL_HEIGHT)
    , m_aspect(1.0)
    , m_mag(INITIAL_MAG)
    , m_fov(45.0)
    , m_camz(8.0)
    , m_xrot(INITIAL_XROT)
    , m_yrot(0.0)
    , m_xoff(0.0)
    , m_yoff(0.0)
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == NULL) {
        printf("Context Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == NULL) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
    position_camera();
    m_last_time_point = std::chrono::high_resolution_clock::now();
}

void View::position_camera()
{
    BoundingBox bb = m_toy->get_model()->bounding_box();

    bb.vmin.v1 -= 2.0;
    bb.vmin.v3 -= 2.0;
    bb.vmax.v1 += 2.0;
    bb.vmax.v3 += 2.0;

    m_radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    m_radius = fmax(m_radius, (bb.vmax.v2 - bb.vmin.v2) / (2.0));
    m_radius = fmax(m_radius, 2.0);
    m_radius *= sqrt(2.0);
    m_center.v1 = (bb.vmin.v1 + bb.vmax.v1) / 2.0;
    m_center.v2 = (bb.vmin.v2 + bb.vmax.v2) / 2.0;
    m_center.v3 = (bb.vmin.v3 + bb.vmax.v3) / 2.0;
//    printf("m_radius = %5.2f, center = (%5.2f, %5.2f, %5.2f)\n", m_radius, m_center.v1, m_center.v2, m_center.v3);
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
    delete m_toy;
    if (m_animation_matrix_uniform != nullptr) {
        delete m_animation_matrix_uniform;
    }
    SDL_DestroyRenderer(m_renderer);
    SDL_GL_DeleteContext(m_context);
    SDL_Quit();
}

bool View::add_shader_from_source_file(GLuint shader, const char* name)
{
    FILE* fin = fopen(name, "r");
    if (fin == NULL) {
        printf("add_shader_from_source_file(%s): File not found\n", name);
        return false;
    }
    struct stat st;
    stat(name, &st);
    int file_size = st.st_size;
    if (file_size <= 0) {
        printf("add_shader_from_source_file(%s): File empty\n", name);
        return false;
    }
    GLchar* src_buffer[1];
    src_buffer[0] = new GLchar[file_size + 1];
    int res = fread(src_buffer[0], 1, file_size, fin);
    if (res != file_size) {
        printf("add_shader_from_source_file(%s): Error reading file\n", name);
        return false;
    }
    fclose(fin);
    GLchar* ptr = src_buffer[0];
    ptr[file_size] = 0;
    glShaderSource(shader, 1, src_buffer, NULL);
    delete [] src_buffer[0];
    glCompileShader(shader);
    GLint shader_compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE) {
        printf("add_shader_from_source_file(%s): Unable to compile file\n", name);
        print_shader_log(shader);
        return false;
    }
    return true;
}

void View::generate_textures()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int width, height, channels;
    unsigned char *data = stbi_load("playfield.png", &width, &height, &channels, 0);
    printf("Image loaded width %d, height %d, channels %d\n", width, height, channels);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
        printf("texture width %d, height %d, channels %d\n", width, height, channels);
    } else {

        printf("failed to load texture\n");
    }
}


void View::initialize()
{
#ifdef VERBOSE
    printf("View::initialize()\n");
#endif
    const char* vshader_name = "vshader.glsl";
    const char* fshader_name = "fshader.glsl";





    GLuint vshader = 0;
    GLuint fshader = 0;
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        printf("Error initializing GLEW: %s\n", glewGetErrorString(glew_error));
        exit(0);
    }
    if (SDL_GL_SetSwapInterval(0) < 0) {
        printf("Warning: Unable to set VSync. SDL Error: %s\n", SDL_GetError());
    }
    glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_program = glCreateProgram();
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!add_shader_from_source_file(vshader, vshader_name)) {
        printf("Error loading vertex shader source '%s'\n", vshader_name);
        exit(0);
    }
    glAttachShader(m_program, vshader);
    if (!add_shader_from_source_file(fshader, fshader_name)) {
        printf("Error loading fragment shader source '%s'\n", fshader_name);
        exit(0);
    }
    glAttachShader(m_program, fshader);
    glLinkProgram(m_program);
    GLint program_success = GL_TRUE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &program_success);
    if (program_success != GL_TRUE) {
        printf("Error ilinking program\n");
        exit(0);
    }
    m_position_attr = glGetAttribLocation(m_program, "a_position");
    if (m_position_attr == -1) {
        printf("a_position is not a valid glsl variable\n");
        exit(0);
    }
    m_color_attr = glGetAttribLocation(m_program, "a_color");
    if (m_color_attr == -1) {
        printf("a_color is not a valid glsl variable\n");
        exit(0);
    }
    m_normal_attr = glGetAttribLocation(m_program, "a_normal");
    if (m_normal_attr == -1) {
        printf("a_normal is not a valid glsl variable\n");
        exit(0);
    }
    m_texture_position_attr = glGetAttribLocation(m_program, "a_texture_position");
    if (m_texture_position_attr == -1) {
        printf("a_texture_position is not a valid glsl variable\n");
        exit(0);
    }
    m_animation_id_attr = glGetAttribLocation(m_program, "a_animation_id");
    if (m_animation_id_attr == -1) {
        printf("a_animation_id is not a valid glsl variable\n");
        exit(0);
    }
    m_texture_id_attr = glGetAttribLocation(m_program, "a_texture_id");
    if (m_texture_id_attr == -1) {
        printf("a_texture_id is not a valid glsl variable\n");
        exit(0);
    }
    m_mvp_matrix_uniform = glGetUniformLocation(m_program, "mvp_matrix");
    if (m_mvp_matrix_uniform == -1) {
        printf("mvp_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_rot_matrix_uniform = glGetUniformLocation(m_program, "rot_matrix");
    if (m_rot_matrix_uniform == -1) {
        printf("rot_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_texture1_uniform = glGetUniformLocation(m_program, "texture1");
    if (m_texture1_uniform == -1) {
        printf("texture1 is not a valid glsl variable\n");
        exit(0);
    }
    generate_textures();
    int n = m_toy->animation_matrices();
    if (n > 0) {
        m_animation_matrix_uniform = new GLint[n];
        for (int i = 0; i < n; i++) {
            char id[256];
            sprintf(id, "animation_%d_matrix", i);
            m_animation_matrix_uniform[i] = glGetUniformLocation(m_program, id);
            if (m_animation_matrix_uniform[i] == -1) {
                printf("'%s' is not a valid glsl variable\n", id);
                exit(0);
            }
        }
    }
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    copy_facets();
}

void View::copy_facets()
{
    m_facet_count = 3 * m_toy->get_model()->facets();
    if (m_facet_count > 0) {
        VertexData* vertices = new VertexData[m_facet_count];
        int vix = 0;
        sub_copy_facets(m_toy->get_model(), vertices, vix);
        // Transfer vertex data to VBO
        glBufferData(GL_ARRAY_BUFFER, m_facet_count * sizeof(VertexData), vertices, GL_STATIC_DRAW);
        delete [] vertices;
    }
}

void View::sub_copy_facets(CadModel* model, VertexData* vertices, int& vix)
{
    float an_id, tx_id;
    Float3 vp, vc, vn;
    Float2 tp;
    for (int i = 0; i < model->facets(); i++) {
        an_id = model->facet_animation_id(i);
        tx_id = model->facet_texture_id(i);
        vc = model->facet_color(i);
        vn = model->facet_normal(i);
        vp = model->facet_v1(i);
        tp = model->facet_texture_v1(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].texture_id = tx_id;
        vertices[vix].texture_position = tp;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
        vp = model->facet_v2(i);
        tp = model->facet_texture_v2(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].texture_id = tx_id;
        vertices[vix].texture_position = tp;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
        vp = model->facet_v3(i);
        tp = model->facet_texture_v3(i);
        vertices[vix].animation_id = an_id;
        vertices[vix].texture_id = tx_id;
        vertices[vix].texture_position = tp;
        vertices[vix].position = vp;
        vertices[vix].normal = vn;
        vertices[vix++].color = vc;
    }
}

void View::resize(int w, int h)
{
#ifdef VERBOSE
    printf("View::resize(%d, %d)\n", w, h);
#endif
    m_width = w;
    m_height = h;
    m_aspect = float(m_width) / float(m_height ? m_height : 1.0);
    glViewport(0, 0, m_width, m_height);
    resize_calc();
}

void View::resize_calc()
{
    float q = tan(m_fov * (PI / 180.0) / 2.0);
    m_camz = m_radius / q;
    m_camz -= m_radius;
    float znear = 0.1;
    float zfar = m_camz + 2.0 * m_radius;
    m_projection.perspective(m_fov / m_mag, m_aspect, znear, zfar);
//    printf("m_fov = %5.3f, m_mag = %5.3f, m_aspect = %5.2f, znear = %5.2f, zfar = %5.2f\n", m_fov, m_mag, m_aspect, znear, zfar);
}

void View::check_storage()
{
    int fc = 3 * m_toy->get_model()->facets();
    if (m_max_vertex_count > fc)
        return;
    m_max_vertex_count = std::max(2 * m_max_vertex_count, 2 * fc);
}

void View::render()
{
#ifdef VERBOSE
    printf("View::render()\n");
#endif
    std::chrono::high_resolution_clock::time_point this_time_point = std::chrono::high_resolution_clock::now();
    unsigned long real_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(this_time_point - m_last_time_point).count();
    m_last_time_point = this_time_point;
    m_toy->advance(real_ns);
    Matrix4x4 matrix;
    matrix.unity();
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.rotate_ax(m_xrot);
    matrix.rotate_ay(m_yrot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_program);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glEnableVertexAttribArray(m_position_attr);
    glEnableVertexAttribArray(m_color_attr);
    glEnableVertexAttribArray(m_normal_attr);
    glEnableVertexAttribArray(m_texture_position_attr);
    glEnableVertexAttribArray(m_animation_id_attr);
    glEnableVertexAttribArray(m_texture_id_attr);
    int stride = sizeof(VertexData);
    char* offset = 0;
    glVertexAttribPointer(m_position_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_normal_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_color_attr, 3, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float3);
    glVertexAttribPointer(m_texture_position_attr, 2, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(Float2);
    glVertexAttribPointer(m_animation_id_attr, 1, GL_FLOAT, GL_FALSE, stride, (void*) offset);
    offset += sizeof(float);
    glVertexAttribPointer(m_texture_id_attr, 1, GL_FLOAT, GL_FALSE, stride, (void*) offset);

    glUniformMatrix4fv(m_mvp_matrix_uniform, 1, GL_TRUE, m_mvp_matrix.data());
    glUniformMatrix4fv(m_rot_matrix_uniform, 1, GL_TRUE, m_rot_matrix.data());
    int n = m_toy->animation_matrices();
    for (int i = 0; i < n; i++) {
        glUniformMatrix4fv(m_animation_matrix_uniform[i], 1, GL_TRUE, m_toy->get_animation_matrix(i).data());
    }

    glUniform1i(m_texture1_uniform, 0);


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, m_facet_count);
    glDisableVertexAttribArray(m_texture_id_attr);
    glDisableVertexAttribArray(m_animation_id_attr);
    glDisableVertexAttribArray(m_texture_position_attr);
    glDisableVertexAttribArray(m_normal_attr);
    glDisableVertexAttribArray(m_color_attr);
    glDisableVertexAttribArray(m_position_attr);
    glUseProgram(0);
    SDL_GL_SwapWindow(m_window);
    glFinish();
    ++m_frame;
}

void View::translate_x(int x)
{
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wx = m_aspect * (m_camz + m_radius) * q;
    float ratio = (float) x / fmax(1.0, (float) m_width);
    float dx = wx * ratio;
    m_xoff += (dx);
}

void View::translate_y(int y)
{
    float q = tan(m_fov * (PI / 180.0) / (2.0 * m_mag));
    float wy = (m_camz + m_radius) * q;
    float ratio = (float) y / fmax(1.0, (float) m_height);
    float dy = wy * ratio;
    m_yoff -= (dy);
}

void View::translate_home()
{
    m_xoff = 0.0;
    m_yoff = 0.0;
}

void View::rotate_ax(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ax(%f)\n", degrees);
#endif
    m_xrot += degrees;
}

void View::rotate_ay(float degrees)
{
#ifdef VERBOSE
    printf("View::rotate_ay(%f)\n", degrees);
#endif
    m_yrot += degrees;
}

void View::rotate_home()
{
#ifdef VERBOSE
    printf("View::rotate_home()\n");
#endif
    m_xrot = INITIAL_XROT;
    m_yrot = 0.0;
}

void View::zoom(float factor)
{
    set_mag(m_mag * factor);
}

void View::zoom_home()
{
    set_mag(INITIAL_MAG);
}

void View::set_mag(float mag)
{
    m_mag = fmax(1.0, mag);
    m_mag = fmin(10.0, m_mag);
    resize_calc();
}

int View::width() const
{
    return m_width;
}

int View::height() const
{
    return m_height;
}

void View::print_program_log(GLuint program)
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void View::print_shader_log(GLuint shader)
{
   //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}

void View::left_action_button(bool on)
{
    m_toy->left_action_button(on);
}

void View::right_action_button(bool on)
{
    m_toy->right_action_button(on);
}

