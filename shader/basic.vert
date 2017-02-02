#version 100

in vec3 VertexPosition;
in vec3 VertexColor;

varying out vec3 Color;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

void main()
{
    Color = VertexColor;

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
