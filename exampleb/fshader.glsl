#version 330 core

in vec4 v_normal;
in vec4 v_color;
in vec2 v_texture_position;
in float v_texture_id;
in float v_animation_id;

uniform float score[24];

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;
uniform sampler2D texture6;
uniform sampler2D texture7;
uniform sampler2D texture8;
uniform sampler2D texture9;
uniform sampler2D texture10;
uniform sampler2D texture11;

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
        if (v_texture_id < 1.5) { // Playfield
            c = 0.7;
            billy = texture(texture1, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 2.5)  { // Plastic1
            c = 1.0;
            billy = texture(texture2, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 3.5)  { // Plastic2
            c = 1.0;
            billy = texture(texture3, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 4.5)  { // Plastic3
            c = 1.0;
            billy = texture(texture4, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 5.5)  { // Plastic4
            c = 1.0;
            billy = texture(texture5, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 6.5)  { // Plastic5
            c = 1.0;
            billy = texture(texture6, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 7.5)  { // Plastic6
            c = 1.0;
            billy = texture(texture7, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 8.5)  { // Plastic7
            c = 1.0;
            billy = texture(texture8, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 9.5)  { // Plastic8
            c = 1.0;
            billy = texture(texture9, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else if (v_texture_id < 10.5)  { // Drop Target
            c = 1.0;
            billy = texture(texture10, v_texture_position);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        } else  {                        // Score
            c = 1.0;
            vec2 ttt;
            if (v_animation_id < 42.5) {
              ttt = vec2(v_texture_position.x + score[0], v_texture_position.y);
            } else if (v_animation_id < 43.5) {
              ttt = vec2(v_texture_position.x + score[1], v_texture_position.y);
            } else if (v_animation_id < 44.5) {
              ttt = vec2(v_texture_position.x + score[2], v_texture_position.y);
            } else if (v_animation_id < 45.5) {
              ttt = vec2(v_texture_position.x + score[3], v_texture_position.y);
            } else if (v_animation_id < 46.5) {
              ttt = vec2(v_texture_position.x + score[4], v_texture_position.y);
            } else if (v_animation_id < 47.5) {
              ttt = vec2(v_texture_position.x + score[5], v_texture_position.y);
            } else if (v_animation_id < 48.5) {
              ttt = vec2(v_texture_position.x + score[6], v_texture_position.y);
            } else if (v_animation_id < 49.5) {
              ttt = vec2(v_texture_position.x + score[7], v_texture_position.y);
            } else if (v_animation_id < 50.5) {
              ttt = vec2(v_texture_position.x + score[8], v_texture_position.y);
            } else if (v_animation_id < 51.5) {
              ttt = vec2(v_texture_position.x + score[9], v_texture_position.y);
            } else if (v_animation_id < 52.5) {
              ttt = vec2(v_texture_position.x + score[10], v_texture_position.y);
            } else if (v_animation_id < 53.5) {
              ttt = vec2(v_texture_position.x + score[11], v_texture_position.y);
            } else if (v_animation_id < 54.5) {
              ttt = vec2(v_texture_position.x + score[12], v_texture_position.y);
            } else if (v_animation_id < 55.5) {
              ttt = vec2(v_texture_position.x + score[13], v_texture_position.y);
            } else if (v_animation_id < 56.5) {
              ttt = vec2(v_texture_position.x + score[14], v_texture_position.y);
            } else if (v_animation_id < 57.5) {
              ttt = vec2(v_texture_position.x + score[15], v_texture_position.y);
            } else if (v_animation_id < 58.5) {
              ttt = vec2(v_texture_position.x + score[16], v_texture_position.y);
            } else if (v_animation_id < 59.5) {
              ttt = vec2(v_texture_position.x + score[17], v_texture_position.y);
            } else if (v_animation_id < 60.5) {
              ttt = vec2(v_texture_position.x + score[18], v_texture_position.y);
            } else if (v_animation_id < 61.5) {
              ttt = vec2(v_texture_position.x + score[19], v_texture_position.y);
            } else if (v_animation_id < 62.5) {
              ttt = vec2(v_texture_position.x + score[20], v_texture_position.y);
            } else if (v_animation_id < 63.5) {
              ttt = vec2(v_texture_position.x + score[21], v_texture_position.y);
            } else if (v_animation_id < 64.5) {
              ttt = vec2(v_texture_position.x + score[22], v_texture_position.y);
            } else {
              ttt = vec2(v_texture_position.x + score[23], v_texture_position.y);
            }
            billy = texture(texture11, ttt);
            billy.r = c * billy.r;
            billy.g = c * billy.g;
            billy.b = c * billy.b;
            gl_FragColor = billy;
        }
    }
}

