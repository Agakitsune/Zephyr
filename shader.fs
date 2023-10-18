#version 400 core

in vec3 color;
in vec2 coord;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
    FragColor = mix(vec4(color, 1.0), texture(tex, coord), 0.5);
} 