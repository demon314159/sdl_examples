
#include "view.h"
#include "matrix4x4.h"
#include <stdio.h>
#include <sys/stat.h>

View::View()
    : m_window(nullptr)
    , m_renderer(nullptr)
    , m_pos_attr(0)
    , m_col_attr(0)
    , m_matrix_uniform(0)
    , m_program(0)
    , m_vao(0)
    , m_vbo(0)
    , m_frame(0)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Video Initialization Error: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_window = SDL_CreateWindow("My Stuff", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        exit(0);
    }
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
}

View::~View()
{
    printf("frames = %d\n", m_frame);
    SDL_DestroyRenderer(m_renderer);
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
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

void View::initialize()
{
    const char* vshader_name = "vshader.glsl";
    const char* fshader_name = "fshader.glsl";
    GLuint vshader = 0;
    GLuint fshader = 0;
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        printf("Error initializing GLEW: %s\n", glewGetErrorString(glew_error));
        exit(0);
    }
    if (SDL_GL_SetSwapInterval(1) < 0) {
        printf("Warning: Unable to set VSync. SDL Error: %s\n", SDL_GetError());
    }
    glClearColor(1.0f, 0.682f, 0.259f, 1.0f); // yellow orange
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_program = glCreateProgram();
    vshader = glCreateShader(GL_VERTEX_SHADER);
    fshader = glCreateShader(GL_FRAGMENT_SHADER);

// Turn these on when solid models introduced
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);

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
    m_pos_attr = glGetAttribLocation(m_program, "posAttr");
    if (m_pos_attr == -1) {
        printf("posAttr is not a valid glsl variable\n");
        exit(0);
    }
    m_col_attr = glGetAttribLocation(m_program, "colAttr");
    if (m_col_attr == -1) {
        printf("colAttr is not a valid glsl variable\n");
        exit(0);
    }
    m_matrix_uniform = glGetUniformLocation(m_program, "matrix");
    if (m_matrix_uniform == -1) {
        printf("matrix is not a valid glsl variable\n");
        exit(0);
    }

    static const GLfloat vertices[] = {
         0.0f,  0.707f, 0.0f,   1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,   0.0f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,   0.0f,   0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void View::render()
{
//    const qreal retinaScale = devicePixelRatio();
//    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
    int w;
    int h;
    SDL_GetWindowSize(m_window, &w, &h);
    SDL_Rect tlv;
    tlv.x = 0;
    tlv.y = 0;
    tlv.w = w;
    tlv.h = h;
    SDL_RenderSetViewport(m_renderer, &tlv);

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_program);
    glEnableVertexAttribArray(m_pos_attr);
    glEnableVertexAttribArray(m_col_attr);
    glVertexAttribPointer(m_pos_attr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) 0);
    glVertexAttribPointer(m_col_attr, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    Matrix4x4 amatrix;
    amatrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    amatrix.translate(0.0f, 0.0f, -2.0f);
//    amatrix.rotate_ay(100.0f * m_frame / 60.0);
    amatrix.rotate_ay(20.0f * m_frame / 60.0);
    glUniformMatrix4fv(m_matrix_uniform, 1, GL_TRUE, amatrix.data());

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(m_col_attr);
    glDisableVertexAttribArray(m_pos_attr);

    glUseProgram(0);
    SDL_GL_SwapWindow(m_window);
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

