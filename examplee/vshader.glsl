#version 330 core

uniform mat4 fixed_matrix;
uniform mat4 hide_fixed_matrix;
uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;

uniform mat4 animation_0_matrix;
uniform mat4 animation_1_matrix;
uniform mat4 animation_2_matrix;
uniform mat4 animation_3_matrix;
uniform mat4 animation_4_matrix;
uniform mat4 animation_5_matrix;
uniform mat4 animation_6_matrix;
uniform mat4 animation_7_matrix;
uniform mat4 animation_8_matrix;
uniform mat4 animation_9_matrix;
uniform mat4 animation_10_matrix;
uniform mat4 animation_11_matrix;
uniform mat4 animation_12_matrix;

in vec3 a_position;
in vec3 a_normal;
in vec3 a_color;
in vec2 a_texture_position;
in float a_animation_id;
in float a_texture_id;

out vec4 v_normal;
out vec4 v_color;
out vec2 v_texture_position;
out float v_texture_id;
out float v_animation_id;

void main()
{
    vec3 billy;
    billy = normalize(a_normal);

// Calculate vertex position in screen space
    if (a_animation_id < 0.5) { // Optimize this most common case
        gl_Position = mvp_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * vec4(billy, 0.0);
        v_color = vec4(a_color, 1.0);
    } else {
        if (a_animation_id < 1.5) {              // Light
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 2.5) {  // Fixed objects
            gl_Position = fixed_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 3.5) {  // Hide Fixed objects
            gl_Position = hide_fixed_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 16.5) {  // Animated objects
            if (a_animation_id < 4.5) {          // Marker
                gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 5.5) {   // Button 1 doesn't hide
                gl_Position = fixed_matrix * animation_1_matrix * vec4(a_position, 1.0);
                v_normal = animation_1_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 6.5) {   // Button 2
                gl_Position = hide_fixed_matrix * animation_2_matrix * vec4(a_position, 1.0);
                v_normal = animation_2_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 7.5) {   // Button 3
                gl_Position = hide_fixed_matrix * animation_3_matrix * vec4(a_position, 1.0);
                v_normal = animation_3_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 8.5) {   // Button 4
                gl_Position = hide_fixed_matrix * animation_4_matrix * vec4(a_position, 1.0);
                v_normal = animation_4_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 9.5) {   // Button 5
                gl_Position = hide_fixed_matrix * animation_5_matrix * vec4(a_position, 1.0);
                v_normal = animation_5_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 10.5) {   // Button 6
                gl_Position = hide_fixed_matrix * animation_6_matrix * vec4(a_position, 1.0);
                v_normal = animation_6_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 11.5) {   // Button 7
                gl_Position = hide_fixed_matrix * animation_7_matrix * vec4(a_position, 1.0);
                v_normal = animation_7_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 12.5) {   // Button 8
                gl_Position = hide_fixed_matrix * animation_8_matrix * vec4(a_position, 1.0);
                v_normal = animation_8_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 13.5) {   // Button 9
                gl_Position = hide_fixed_matrix * animation_9_matrix * vec4(a_position, 1.0);
                v_normal = animation_9_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 14.5) {   // Button 10
                gl_Position = hide_fixed_matrix * animation_10_matrix * vec4(a_position, 1.0);
                v_normal = animation_10_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 15.5) {   // Button 11
                gl_Position = hide_fixed_matrix * animation_11_matrix * vec4(a_position, 1.0);
                v_normal = animation_11_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 16.5) {   // Table
                gl_Position = mvp_matrix * animation_12_matrix * vec4(a_position, 1.0);
                v_normal = vec4(0.0, 0.0, 1.0, 0.0);
            }
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 99.5) { // Transparent
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
            v_color = vec4(a_color, 0.0);
        } else { // Treat remaining like 0.0
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        }
    }
    v_texture_position = a_texture_position;
    v_texture_id = a_texture_id;
    v_animation_id = a_animation_id;
}

