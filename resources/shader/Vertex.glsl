#version 110 core

in vec3 in_position;
in vec3 in_color;

uniform mat4 uni_modelMatrix;
uniform mat4 uni_viewMatrix;
uniform mat4 uni_projectionMatrix;

varying vec3 color;

void main()
{
    vec4 worldPosition = uni_modelMatrix * vec4(in_position, 1.0);
    gl_Position = uni_projectionMatrix * uni_viewMatrix * worldPosition;
    color = in_color;
};