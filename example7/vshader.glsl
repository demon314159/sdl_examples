uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;
uniform mat4 animation_0_matrix;
uniform mat4 animation_1_matrix;
uniform mat4 animation_2_matrix;
uniform mat4 animation_3_matrix;

attribute vec3 a_position;
attribute vec3 a_normal;
attribute vec3 a_color;
attribute float a_animation_id;

varying vec4 v_normal;
varying vec4 v_color;

void main()
{
    vec3 billy;
    billy = normalize(a_normal);

// Calculate vertex position in screen space
    if (a_animation_id == 0.0) { // Optimize this most common case
        gl_Position = mvp_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * vec4(billy, 0.0);
    } else {

// This should be generated automatically based on number of animation matrices
        if (a_animation_id == 2.0) {
            gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
        } else if (a_animation_id == 3.0) {
            gl_Position = mvp_matrix * animation_1_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * animation_1_matrix * vec4(billy, 0.0);

        } else if (a_animation_id == 4.0) {
            gl_Position = mvp_matrix * animation_2_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * animation_2_matrix * vec4(billy, 0.0);
        } else if (a_animation_id == 5.0) {
            gl_Position = mvp_matrix * animation_3_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * animation_3_matrix * vec4(billy, 0.0);
// end of animation_matrix stuff

        } else if (a_animation_id == 1.0) {
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
        } else { // Treat unknowns like 0.0
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * vec4(billy, 0.0);
        }
    }
    // Pass color coordinate to fragment shader
    v_color = vec4(a_color, 1.0);
}
