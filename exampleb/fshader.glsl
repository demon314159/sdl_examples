#version 330 core

in vec4 v_normal;
in vec4 v_color;
in vec2 v_texture_position;
in float v_texture_id;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;

void main()
{
    float c = abs(v_normal.z);
    vec4 billy;
    if (v_texture_id < 0.5) {
        billy.r = c * v_color.r;
        billy.g = c * v_color.g;
        billy.b = c * v_color.b;
        billy.a = v_color.a;
        gl_FragColor = billy;
    } else {
        if (v_texture_id < 1.5) {
            c = 0.7;
            billy = texture(texture1, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 2.5)  {
            c = 1.0;
            billy = texture(texture2, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 3.5)  {
            c = 1.0;
            billy = texture(texture3, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 4.5)  {
            c = 1.0;
            billy = texture(texture4, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 5.5)  {
            c = 1.0;
            billy = texture(texture5, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 6.5)  {
            c = 1.0;
            billy = texture(texture6, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else  {
            c = 1.0;
            billy = texture(texture7, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        }
    }
}

