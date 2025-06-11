#version 410 core

uniform float uDelta;
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = vec4(0.5, 0, 0.5, 1.0);
}
