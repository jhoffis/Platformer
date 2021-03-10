#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 passColor; // output a color to the fragment shader
out vec2 passTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform int flipSideways;

void main()
{
    gl_Position =
//    projection * view *
    model * view * vec4(position, 1.0);
    passColor = color;

    // FIXME Denne tegner hopping når den er baklengs fordi det er motsatt av idle
    if (flipSideways != 0) {
        passTexCoord = vec2(1.0 - texCoord.s, texCoord.t);
    } else {
        passTexCoord = texCoord;
    }
}