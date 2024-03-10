#version 330 core

varying vec4 v_normal;
varying vec4 v_color;
varying vec2 v_texture_position;
varying float v_texture_id;

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
        gl_FragColor = texture(texture1, v_texture_position);
    }
}

