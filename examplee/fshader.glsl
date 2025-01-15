#version 330 core

in vec4 v_normal;
in vec4 v_color;
in vec2 v_texture_position;
in float v_texture_id;
in float v_animation_id;

uniform float table_size[2];

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;

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
        if (v_texture_id < 1.5) { // First texture
            billy = texture(texture1, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 2.5) { // Second texture
            billy = texture(texture2, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 3.5) { // Third texture
            billy = texture(texture3, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 4.5) { // Fourth texture
            billy = texture(texture4, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 5.5) { // Fifth texture
            billy = texture(texture5, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 6.5) { // Sixth texture
            billy = texture(texture6, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 7.5) { // Seventh texture
            billy = texture(texture7, v_texture_position);
            gl_FragColor = billy;
        } else if (v_texture_id < 8.5) { // Eighth texture
            vec2 ttt;
            ttt = vec2(v_texture_position.x * table_size[0], v_texture_position.y * table_size[1]);
            gl_FragColor = texture(texture8, ttt);
        }
    }
}

