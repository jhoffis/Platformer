in vec3 position;   // the position variable has attribute position 0
in vec3 color; // the color variable has attribute position 1
in vec2 texCoord;

out vec3 passColor; // output a color to the fragment shader
out vec2 passTexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    passColor = color; // set ourColor to the input color we got from the vertex data
    passTexCoord = texCoord;
}       