#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 passColor; // output a color to the fragment shader
out vec2 passTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position =
//    projection * view *
    model * view * vec4(position, 1.0);
    passColor = color; // set ourColor to the input color we got from the vertex data
    passTexCoord = texCoord;
}       