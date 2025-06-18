#version 410 core

uniform float uOffset;
uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;


layout(location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;


void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos * cos(uOffset), 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
