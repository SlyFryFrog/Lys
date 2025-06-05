#version 410 core

uniform float uDelta;
out vec4 FragColor;

void main()
{
    FragColor = vec4(uDelta, 1.0, 0.0, 1.0);
}
