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
    if (a_animation_id < 0.5) { // Optimize this most common case
        gl_Position = mvp_matrix * vec4(a_position, 1.0);
        v_normal = rot_matrix * vec4(billy, 0.0);
        v_color = vec4(a_color, 1.0);
    } else {
        if (a_animation_id < 1.5) {              // Light
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 5.5) {       // Animated objects
            if (a_animation_id < 2.5) {          // Left Flipper
                gl_Position = mvp_matrix * animation_0_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_0_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 3.5) {   // Right Flipper
                gl_Position = mvp_matrix * animation_1_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_1_matrix * vec4(billy, 0.0);
            } else if (a_animation_id < 4.5) {   // Top Flipper
                gl_Position = mvp_matrix * animation_2_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_2_matrix * vec4(billy, 0.0);
            } else {                             // Ball
                gl_Position = mvp_matrix * animation_3_matrix * vec4(a_position, 1.0);
                v_normal = rot_matrix * animation_3_matrix * vec4(billy, 0.0);
            }
            v_color = vec4(a_color, 1.0);

        } else if (a_animation_id < 20.5) { // 15 Drop Targets
            if (a_animation_id < 6.5) {          // Drop Target1
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[0], a_position.z, 1.0);
            } else if (a_animation_id < 7.5) {   // Drop Target2
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[1], a_position.z, 1.0);
            } else if (a_animation_id < 8.5) {   // Drop Target3
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[2], a_position.z, 1.0);
            } else if (a_animation_id < 9.5) {   // Drop Target4
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[3], a_position.z, 1.0);
            } else if (a_animation_id < 10.5) {  // Drop Target5
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[4], a_position.z, 1.0);
            } else if (a_animation_id < 11.5) {  // Drop Target6
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[5], a_position.z, 1.0);
            } else if (a_animation_id < 12.5) {  // Drop Target7
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[6], a_position.z, 1.0);
            } else if (a_animation_id < 13.5) {  // Drop Target8
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[7], a_position.z, 1.0);
            } else if (a_animation_id < 14.5) {  // Drop Target9
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[8], a_position.z, 1.0);
            } else if (a_animation_id < 15.5) {  // Drop Target10
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[9], a_position.z, 1.0);
            } else if (a_animation_id < 16.5) {  // Drop Target11
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[10], a_position.z, 1.0);
            } else if (a_animation_id < 17.5) {  // Drop Target12
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[11], a_position.z, 1.0);
            } else if (a_animation_id < 18.5) {  // Drop Target23
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[12], a_position.z, 1.0);
            } else if (a_animation_id < 19.5) {  // Drop Target14
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[13], a_position.z, 1.0);
            } else {                             // Drop Target15
                gl_Position = mvp_matrix * vec4(a_position.x, a_position.y - target_height[14], a_position.z, 1.0);
            }
            v_normal = rot_matrix * vec4(billy, 0.0);
            v_color = vec4(a_color, 1.0);
        } else if (a_animation_id < 41.5) { // 21 Lamps
            if (a_animation_id < 21.5) {         // Lamp1
                v_color = vec4(lamp_color[0], 1.0);
            } else if (a_animation_id < 22.5) {  // Lamp2
                v_color = vec4(lamp_color[1], 1.0);
            } else if (a_animation_id < 23.5) {  // Lamp3
                v_color = vec4(lamp_color[2], 1.0);
            } else if (a_animation_id < 24.5) {  // Lamp4
                v_color = vec4(lamp_color[3], 1.0);
            } else if (a_animation_id < 25.5) {  // Lamp5
                v_color = vec4(lamp_color[4], 1.0);
            } else if (a_animation_id < 26.5) {  // Lamp6
                v_color = vec4(lamp_color[5], 1.0);
            } else if (a_animation_id < 27.5) {  // Lamp7
                v_color = vec4(lamp_color[6], 1.0);
            } else if (a_animation_id < 28.5) {  // Lamp8
                v_color = vec4(lamp_color[7], 1.0);
            } else if (a_animation_id < 29.5) {  // Lamp9
                v_color = vec4(lamp_color[8], 1.0);
            } else if (a_animation_id < 30.5) {  // Lamp10
                v_color = vec4(lamp_color[9], 1.0);
            } else if (a_animation_id < 31.5) {  // Lamp11
                v_color = vec4(lamp_color[10], 1.0);
            } else if (a_animation_id < 32.5) {  // Lamp12
                v_color = vec4(lamp_color[11], 1.0);
            } else if (a_animation_id < 33.5) {  // Lamp13
                v_color = vec4(lamp_color[12], 1.0);
            } else if (a_animation_id < 34.5) {  // Lamp14
                v_color = vec4(lamp_color[13], 1.0);
            } else if (a_animation_id < 35.5) {  // Lamp15
                v_color = vec4(lamp_color[14], 1.0);
            } else if (a_animation_id < 36.5) {  // Lamp16
                v_color = vec4(lamp_color[15], 1.0);
            } else if (a_animation_id < 37.5) {  // Lamp17
                v_color = vec4(lamp_color[16], 1.0);
            } else if (a_animation_id < 38.5) {  // Lamp18
                v_color = vec4(lamp_color[17], 1.0);
            } else if (a_animation_id < 39.5) {  // Lamp19
                v_color = vec4(lamp_color[18], 1.0);
            } else if (a_animation_id < 40.5) {  // Lamp20
                v_color = vec4(lamp_color[19], 1.0);
            } else {                             // Lamp21
                v_color = vec4(lamp_color[20], 1.0);
            }
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = vec4(0.0, 0.0, 1.0, 0.0);
        } else if (a_animation_id < 98.5) { // Reserved, treat like 0.0
            gl_Position = mvp_matrix * vec4(a_position, 1.0);
            v_normal = rot_matrix * vec4(billy, 0.0);
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
}

