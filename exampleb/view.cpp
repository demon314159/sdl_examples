//
// view.cpp
//

#include "view.h"
#include "lamp.h"
#include "matrix4x4.h"
#include "matrix3x3.h"
#include "paint_can.h"
#include "bounding_box.h"
#include "look.h"
#include "pi.h"
#include "toy.h"

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
    , m_vao(0)
    , m_vbo(0)
    , m_frame(0)
    , m_max_vertex_count(1024 * 1024)
    , m_vertex_count(0)
    , m_toy(new Toy())
{
#ifdef VERBOSE
    printf("View::View(doc)\n");
#endif
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video Initialization Error: %s\n", SDL_GetError());
        exit(0);
    }
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
    BoundingBox bb = m_toy->model()->bounding_box();
    float radius = fmax(fabs(bb.vmax.v1 - bb.vmin.v1) / 2.0, fabs(bb.vmax.v3 - bb.vmin.v3) / 2.0);
    radius = fmax(radius, (bb.vmax.v2 - bb.vmin.v2) / (2.0));
    radius = fmax(radius, 0.1);
    radius *= sqrt(2.0);
    Float3 center = {(bb.vmin.v1 + bb.vmax.v1) / 2.0f, (bb.vmin.v2 + bb.vmax.v2) / 2.0f, (bb.vmin.v3 + bb.vmax.v3) / 2.0f};
    m_toy->camera()->set_target_position(radius, center);
}

View::~View()
{
#ifdef VERBOSE
    printf("View::~View()\n");
#endif
    delete m_toy;
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
    Texture* texture = m_toy->texture();
    int total_textures = texture->textures();
    GLuint* buf = new GLuint[total_textures];
    glGenTextures(total_textures, buf);
    for (int i = 0; i < total_textures; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, buf[i]);
        generate_texture(texture->file_name(i));
    }
    delete [] buf;
}

void View::generate_texture(const char* fname)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    int width, height, channels;
    width = 0;
    height = 0;
    channels = 0;
    unsigned char *data = stbi_load(fname, &width, &height, &channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        printf("failed to load texture\n");
    }
}

Camera* View::camera()
{
    return m_toy->camera();
}

void View::initialize()
{
#ifdef VERBOSE
    printf("View::initialize()\n");
#endif
    m_toy->initialize();
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


#ifdef NEVERMORE
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
    m_scoreboard_mvp_matrix_uniform = glGetUniformLocation(m_program, "scoreboard_mvp_matrix");
    if (m_scoreboard_mvp_matrix_uniform == -1) {
        printf("scoreboard_mvp_matrix is not a valid glsl variable\n");
        exit(0);
    }
    m_scoreboard_rot_matrix_uniform = glGetUniformLocation(m_program, "scoreboard_rot_matrix");
    if (m_scoreboard_rot_matrix_uniform == -1) {
        printf("scoreboard_rot_matrix is not a valid glsl variable\n");
        exit(0);
    }
#endif


    Uniform* u = m_toy->uniform();
    for (int i = 0; i < u->uniforms(); i++) {
        GLint handle = glGetUniformLocation(m_program, u->name(i));
        if (handle == -1) {
            printf("'%s' is not a valid glsl variable\n", u->name(i));
            exit(0);
        }
        u->set_handle(i, handle);
    }
    generate_textures();
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    copy_facets();
}

void View::copy_facets()
{
    int facet_count = m_toy->model()->facets();
    printf("Total number of facets = %d\n", facet_count);
    m_vertex_count = 3 * facet_count;
    if (m_vertex_count > 0) {
        VertexData* vertices = new VertexData[m_vertex_count];
        int vix = 0;
        sub_copy_facets(m_toy->model(), vertices, vix);
        // Transfer vertex data to VBO
        glBufferData(GL_ARRAY_BUFFER, m_vertex_count * sizeof(VertexData), vertices, GL_STATIC_DRAW);
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
    glViewport(0, 0, w, h);
    m_toy->camera()->resize(w, h);
}

void View::check_storage()
{
    int fc = 3 * m_toy->model()->facets();
    if (m_max_vertex_count > fc)
        return;
    m_max_vertex_count = std::max(2 * m_max_vertex_count, 2 * fc);
}

void View::render()
{
    std::chrono::high_resolution_clock::time_point this_time_point = std::chrono::high_resolution_clock::now();
    unsigned long real_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(this_time_point - m_last_time_point).count();
    m_last_time_point = this_time_point;
    m_toy->advance(real_ns);

#ifdef NEVERMORE
    Matrix4x4 matrix;
    matrix.unity();
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.rotate_ay(m_yrot);
    matrix.rotate_ax(m_xrot);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_mvp_matrix = m_projection * matrix;
    m_rot_matrix = matrix;

    matrix.unity();
    matrix.translate(m_xoff, m_yoff, -m_camz - m_radius);
    matrix.translate(-m_center.v1, -m_center.v2, -m_center.v3);
    m_scoreboard_mvp_matrix = m_projection * matrix;
    m_scoreboard_rot_matrix = matrix;
#endif

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

    Uniform* u = m_toy->uniform();
    for (int i = 0; i < u->uniforms(); i++) {
        switch (u->uniform_type(i)) {
            case UNIFORM_TYPE_MATRIX4_FLOAT_VECTOR:
                glUniformMatrix4fv(u->handle(i), u->items(i), GL_TRUE, (float*) u->data(i));
                break;
            case UNIFORM_TYPE_3_FLOAT_VECTOR:
                glUniform3fv(u->handle(i), u->items(i), (float*) u->data(i));
                break;
            case UNIFORM_TYPE_1_FLOAT_VECTOR:
                glUniform1fv(u->handle(i), u->items(i), (float*) u->data(i));
                break;
            case UNIFORM_TYPE_1_INTEGER_VECTOR:
                glUniform1iv(u->handle(i), u->items(i), (GLint*) u->data(i));
                break;
            default:
                break;
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
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

void View::button(int code, bool shifted, bool on)
{
    m_toy->button(code, shifted, on);
}

