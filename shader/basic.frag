#version 100

precision mediump float;

in vec3 Color;

varying out vec4 FragColor;

void main() {
    FragColor = vec4(Color, 255.0);
}
