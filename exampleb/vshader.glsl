#version 330 core

uniform mat4 mvp_matrix;
uniform mat4 rot_matrix;
uniform mat4 animation_0_matrix;
uniform mat4 animation_1_matrix;
uniform mat4 animation_2_matrix;
uniform mat4 animation_3_matrix;
uniform vec3 lamp_color[21];
uniform float target_height[15];

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
        } else if (a_animation_id < 300.0) {
            //
            // Drop targets use 200.0 to 299.0
            //
            if (a_animation_id == 200.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[0], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 201.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[1], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 202.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[2], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 203.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[3], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 204.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[4], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 205.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[5], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 206.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[6], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 207.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[7], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 208.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[8], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 209.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[9], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 210.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[10], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 211.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[11], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 212.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[12], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 213.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[13], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else if (a_animation_id == 214.0) {
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[14], a_position.z, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            } else {
                gl_Position = mvp_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * vec4(billy, 0.0);
            }
        } else { // Treat unknowns like 0.0
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * vec4(billy, 0.0);
        }
    }
    // Pass color coordinate to fragment shader
    if (a_animation_id == 99.0) {
        v_color = vec4(a_color, 0.0);
    } else if (a_animation_id < 200.0) {

        //
        // Lamps use 100.0 to 199.0
        //

        if (a_animation_id == 100.0) {
            v_color = vec4(lamp_color[0], 1.0);
        } else if (a_animation_id == 101.0) {
            v_color = vec4(lamp_color[1], 1.0);
        } else if (a_animation_id == 102.0) {
            v_color = vec4(lamp_color[2], 1.0);
        } else if (a_animation_id == 103.0) {
            v_color = vec4(lamp_color[3], 1.0);
        } else if (a_animation_id == 104.0) {
            v_color = vec4(lamp_color[4], 1.0);
        } else if (a_animation_id == 105.0) {
            v_color = vec4(lamp_color[5], 1.0);
        } else if (a_animation_id == 106.0) {
            v_color = vec4(lamp_color[6], 1.0);
        } else if (a_animation_id == 107.0) {
            v_color = vec4(lamp_color[7], 1.0);
        } else if (a_animation_id == 108.0) {
            v_color = vec4(lamp_color[8], 1.0);
        } else if (a_animation_id == 109.0) {
            v_color = vec4(lamp_color[9], 1.0);
        } else if (a_animation_id == 110.0) {
            v_color = vec4(lamp_color[10], 1.0);
        } else if (a_animation_id == 111.0) {
            v_color = vec4(lamp_color[11], 1.0);
        } else if (a_animation_id == 112.0) {
            v_color = vec4(lamp_color[12], 1.0);
        } else if (a_animation_id == 113.0) {
            v_color = vec4(lamp_color[13], 1.0);
        } else if (a_animation_id == 114.0) {
            v_color = vec4(lamp_color[14], 1.0);
        } else if (a_animation_id == 115.0) {
            v_color = vec4(lamp_color[15], 1.0);
        } else if (a_animation_id == 116.0) {
            v_color = vec4(lamp_color[16], 1.0);
        } else if (a_animation_id == 117.0) {
            v_color = vec4(lamp_color[17], 1.0);
        } else if (a_animation_id == 118.0) {
            v_color = vec4(lamp_color[18], 1.0);
        } else if (a_animation_id == 119.0) {
            v_color = vec4(lamp_color[19], 1.0);
        } else if (a_animation_id == 120.0) {
            v_color = vec4(lamp_color[20], 1.0);
        } else {
            v_color = vec4(a_color, 1.0);
        }
    } else {
        v_color = vec4(a_color, 1.0);
    }
    v_texture_position = a_texture_position;
    v_texture_id = a_texture_id;

}
