#version 330 core

uniform mat4 fixed_matrix;
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
uniform mat4 animation_22_matrix;
uniform mat4 animation_23_matrix;
uniform mat4 animation_24_matrix;
uniform mat4 animation_25_matrix;
uniform mat4 animation_26_matrix;
uniform mat4 animation_27_matrix;
uniform mat4 animation_28_matrix;
uniform mat4 animation_29_matrix;
uniform mat4 animation_30_matrix;
uniform mat4 animation_31_matrix;
uniform mat4 animation_32_matrix;
uniform mat4 animation_33_matrix;
uniform mat4 animation_34_matrix;
uniform mat4 animation_35_matrix;
uniform mat4 animation_36_matrix;
uniform mat4 animation_37_matrix;
uniform mat4 animation_38_matrix;
uniform mat4 animation_39_matrix;
uniform mat4 animation_40_matrix;
uniform mat4 animation_41_matrix;
uniform mat4 animation_42_matrix;
uniform mat4 animation_43_matrix;
uniform mat4 animation_44_matrix;

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
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 2.5) {  // Fixed objects
            gl_Position = fixed_matrix * vec4(a_position, 1.0);
            v_normal = vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 11.5) {  // Animated objects
            if (a_animation_id < 3.5) {          // Marker
                gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 4.5) {   // Button 1
                gl_Position = fixed_matrix * animation_1_matrix * vec4(a_position, 1.0);
                v_normal = animation_1_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 5.5) {   // Button 2
                gl_Position = fixed_matrix * animation_2_matrix * vec4(a_position, 1.0);
                v_normal = animation_2_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 6.5) {   // Button 3
                gl_Position = fixed_matrix * animation_3_matrix * vec4(a_position, 1.0);
                v_normal = animation_3_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 7.5) {   // Button 4
                gl_Position = fixed_matrix * animation_4_matrix * vec4(a_position, 1.0);
                v_normal = animation_4_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 8.5) {   // Button 5
                gl_Position = fixed_matrix * animation_5_matrix * vec4(a_position, 1.0);
                v_normal = animation_5_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 9.5) {   // Button 6
                gl_Position = fixed_matrix * animation_6_matrix * vec4(a_position, 1.0);
                v_normal = animation_6_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 10.5) {   // Button 7
                gl_Position = fixed_matrix * animation_7_matrix * vec4(a_position, 1.0);
                v_normal = animation_7_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 11.5) {   // Button 8
                gl_Position = fixed_matrix * animation_8_matrix * vec4(a_position, 1.0);
                v_normal = animation_8_matrix * vec4(billy, 0.0);
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

