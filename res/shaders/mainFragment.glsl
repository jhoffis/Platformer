precision mediump float;
in vec3 passColor;
in vec2 passTexCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, passTexCoord); // * vec4(passColor, 1.0);
}