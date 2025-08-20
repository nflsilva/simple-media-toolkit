#version 330 core

layout (location = 0) in vec3 vi_position;
layout (location = 1) in vec4 vi_color;

uniform mat4 ui_modelMatrix;
uniform mat4 ui_viewMatrix;
uniform mat4 ui_projectionMatrix;

varying vec4 fi_color;

void main()
{
    //vec4 worldPosition = ui_modelMatrix * vec4(vi_position, 1.0);
    gl_Position = vec4(vi_position, 1.0); //ui_projectionMatrix * ui_viewMatrix * worldPosition;
    fi_color = vi_color;
};
