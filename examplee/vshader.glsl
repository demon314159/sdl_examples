#version 330 core

uniform mat4 fixed_left_matrix;
uniform mat4 fixed_right_matrix;
uniform mat4 hide_left_matrix;
uniform mat4 hide_right_matrix;
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
uniform mat4 animation_13_matrix;
uniform mat4 animation_14_matrix;
uniform mat4 animation_15_matrix;
uniform mat4 animation_16_matrix;
uniform mat4 animation_17_matrix;
uniform mat4 animation_18_matrix;
uniform mat4 animation_19_matrix;
uniform mat4 animation_20_matrix;
uniform mat4 animation_21_matrix;

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
        } else if (a_animation_id < 2.5) {  // Fixed left objects
            gl_Position = fixed_left_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 3.5) {  // Fixed right objects
            gl_Position = fixed_right_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 4.5) {  // Hide Left Fixed objects
            gl_Position = hide_left_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 5.5) {  // Hide Right Fixed objects
            gl_Position = hide_right_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 6.5) { // Marker
            gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 17.5) {  // Left Menu Animated objects
            if (a_animation_id < 7.5) {   // Button 1 doesn't hide
                gl_Position = fixed_left_matrix * animation_1_matrix * vec4(a_position, 1.0);
                v_normal = animation_1_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 8.5) {   // Button 2
                gl_Position = hide_left_matrix * animation_2_matrix * vec4(a_position, 1.0);
                v_normal = animation_2_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 9.5) {   // Button 3
                gl_Position = hide_left_matrix * animation_3_matrix * vec4(a_position, 1.0);
                v_normal = animation_3_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 10.5) {   // Button 4
                gl_Position = hide_left_matrix * animation_4_matrix * vec4(a_position, 1.0);
                v_normal = animation_4_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 11.5) {   // Button 5
                gl_Position = hide_left_matrix * animation_5_matrix * vec4(a_position, 1.0);
                v_normal = animation_5_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 12.5) {   // Button 6
                gl_Position = hide_left_matrix * animation_6_matrix * vec4(a_position, 1.0);
                v_normal = animation_6_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 13.5) {   // Button 7
                gl_Position = hide_left_matrix * animation_7_matrix * vec4(a_position, 1.0);
                v_normal = animation_7_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 14.5) {   // Button 8
                gl_Position = hide_left_matrix * animation_8_matrix * vec4(a_position, 1.0);
                v_normal = animation_8_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 15.5) {   // Button 9
                gl_Position = hide_left_matrix * animation_9_matrix * vec4(a_position, 1.0);
                v_normal = animation_9_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 16.5) {   // Button 10
                gl_Position = hide_left_matrix * animation_10_matrix * vec4(a_position, 1.0);
                v_normal = animation_10_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 17.5) {   // Button 11
                gl_Position = hide_left_matrix * animation_11_matrix * vec4(a_position, 1.0);
                v_normal = animation_11_matrix * vec4(billy, 0.0);
            }
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 26.5) { // Right Menu Animated objects
            if (a_animation_id < 18.5) {   // Button 12 doesn't hide
                gl_Position = fixed_right_matrix * animation_12_matrix * vec4(a_position, 1.0);
                v_normal = animation_12_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 19.5) {   // Button 13
                gl_Position = hide_right_matrix * animation_13_matrix * vec4(a_position, 1.0);
                v_normal = animation_13_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 20.5) {   // Button 14
                gl_Position = hide_right_matrix * animation_14_matrix * vec4(a_position, 1.0);
                v_normal = animation_14_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 21.5) {   // Button 15
                gl_Position = hide_right_matrix * animation_15_matrix * vec4(a_position, 1.0);
                v_normal = animation_15_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 22.5) {   // Button 16
                gl_Position = hide_right_matrix * animation_16_matrix * vec4(a_position, 1.0);
                v_normal = animation_16_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 23.5) {   // Button 17
                gl_Position = hide_right_matrix * animation_17_matrix * vec4(a_position, 1.0);
                v_normal = animation_17_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 24.5) {   // Button 18
                gl_Position = hide_right_matrix * animation_18_matrix * vec4(a_position, 1.0);
                v_normal = animation_18_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 25.5) {   // Button 19
                gl_Position = hide_right_matrix * animation_19_matrix * vec4(a_position, 1.0);
                v_normal = animation_19_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 26.5) {   // Button 20
                gl_Position = hide_right_matrix * animation_20_matrix * vec4(a_position, 1.0);
                v_normal = animation_20_matrix * vec4(billy, 0.0);
            }
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 27.5) {   // Table
            gl_Position = mvp_matrix * animation_21_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
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

