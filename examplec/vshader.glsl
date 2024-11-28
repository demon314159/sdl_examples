#version 330 core

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
        } else if (a_animation_id < 41.5) {  // Animated objects
            if (a_animation_id < 2.5) {          // Token 0
                gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 3.5) {   // Token 1
                gl_Position = mvp_matrix * animation_1_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_1_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 4.5) {   // Token 2
                gl_Position = mvp_matrix * animation_2_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_2_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 5.5) {   // Token 3
                gl_Position = mvp_matrix * animation_3_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_3_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 6.5) {   // Token 4
                gl_Position = mvp_matrix * animation_4_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_4_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 7.5) {   // Token 5
                gl_Position = mvp_matrix * animation_5_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_5_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 8.5) {   // Token 6
                gl_Position = mvp_matrix * animation_6_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_6_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 9.5) {   // Token 7
                gl_Position = mvp_matrix * animation_7_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_7_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 10.5) {   // Token 8
                gl_Position = mvp_matrix * animation_8_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_8_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 11.5) {   // Token 9
                gl_Position = mvp_matrix * animation_9_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_9_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 12.5) {   // Token 10
                gl_Position = mvp_matrix * animation_10_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_10_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 13.5) {   // Token 11
                gl_Position = mvp_matrix * animation_11_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_11_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 14.5) {   // Token 12
                gl_Position = mvp_matrix * animation_12_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_12_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 15.5) {   // Token 13
                gl_Position = mvp_matrix * animation_13_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_13_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 16.5) {   // Token 14
                gl_Position = mvp_matrix * animation_14_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_14_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 17.5) {   // Token 15
                gl_Position = mvp_matrix * animation_15_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_15_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 18.5) {   // Token 16
                gl_Position = mvp_matrix * animation_16_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_16_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 19.5) {   // Token 17
                gl_Position = mvp_matrix * animation_17_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_17_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 20.5) {   // Token 18
                gl_Position = mvp_matrix * animation_18_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_18_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 21.5) {   // Token 19
                gl_Position = mvp_matrix * animation_19_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_19_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 22.5) {   // Token 20
                gl_Position = mvp_matrix * animation_20_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_20_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 23.5) {   // Token 21
                gl_Position = mvp_matrix * animation_21_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_21_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 24.5) {   // Token 22
                gl_Position = mvp_matrix * animation_22_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_22_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 25.5) {   // Token 23
                gl_Position = mvp_matrix * animation_23_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_23_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 26.5) {   // Token 24
                gl_Position = mvp_matrix * animation_24_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_24_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 27.5) {   // Token 25
                gl_Position = mvp_matrix * animation_25_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_25_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 28.5) {   // Token 26
                gl_Position = mvp_matrix * animation_26_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_26_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 29.5) {   // Token 27
                gl_Position = mvp_matrix * animation_27_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_27_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 30.5) {   // Token 28
                gl_Position = mvp_matrix * animation_28_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_28_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 31.5) {   // Token 29
                gl_Position = mvp_matrix * animation_29_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_29_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 32.5) {   // Token 30
                gl_Position = mvp_matrix * animation_30_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_30_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 33.5) {   // Token 31
                gl_Position = mvp_matrix * animation_31_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_31_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 34.5) {   // Token 32
                gl_Position = mvp_matrix * animation_32_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_32_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 35.5) {   // Token 33
                gl_Position = mvp_matrix * animation_33_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_33_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 36.5) {   // Token 34
                gl_Position = mvp_matrix * animation_34_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_34_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 37.5) {   // Token 35
                gl_Position = mvp_matrix * animation_35_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_35_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 38.5) {   // Token 36
                gl_Position = mvp_matrix * animation_36_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_36_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 39.5) {   // Token 37
                gl_Position = mvp_matrix * animation_37_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_37_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 40.5) {   // Token 38
                gl_Position = mvp_matrix * animation_38_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_38_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 41.5) {   // Token 39
                gl_Position = mvp_matrix * animation_39_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_39_matrix * vec4(billy, 0.0);
            }
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 46.5) {
            if (a_animation_id < 42.5) {   // PushButton Clear
                gl_Position = mvp_matrix * animation_40_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_40_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 43.5) {   // PushButton Next
                gl_Position = mvp_matrix * animation_41_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_41_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 44.5) {   // PushButton Back
                gl_Position = mvp_matrix * animation_42_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_42_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 45.5) {   // PushButton Quit
                gl_Position = mvp_matrix * animation_43_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_43_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 46.5) {   // PushButton Help
                gl_Position = mvp_matrix * animation_44_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_44_matrix * vec4(billy, 0.0);
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

