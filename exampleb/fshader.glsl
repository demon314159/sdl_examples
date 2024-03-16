#version 330 core

in vec4 v_normal;
in vec4 v_color;
in vec2 v_texture_position;
in float v_texture_id;

uniform sampler2D texture1;

void main()
{
    float c = abs(v_normal.z);
    vec4 billy;
    if (v_texture_id == 0.0) {
        billy.r = c * v_color.r;
        billy.g = c * v_color.g;
        billy.b = c * v_color.b;
        billy.a = v_color.a;
        gl_FragColor = billy;
    } else {
        c = 0.6;
        billy = texture(texture1, v_texture_position);
        billy.r = c * billy.r;
        billy.g = c * billy.g;
        billy.b = c * billy.b;
        gl_FragColor = billy;
    }
}

