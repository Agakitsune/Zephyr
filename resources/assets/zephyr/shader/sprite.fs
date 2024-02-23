#version 400 core

in vec2 coord;

uniform sampler2D Texture;
uniform vec4 color;

out vec4 FragColor;

void main()
{
    vec4 texel = texture(Texture, coord);
    FragColor = color * texel;
}
