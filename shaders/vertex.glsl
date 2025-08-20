#version 330 core

layout (location = 0) in vec3 vi_position;
layout (location = 1) in vec2 vi_textureCoords;

uniform mat4 uni_modelMatrix;
uniform mat4 uni_viewMatrix;
uniform mat4 uni_projectionMatrix;

out vec2 fi_textureCoords;

void main()
{
    //vec4 worldPosition = ui_modelMatrix * vec4(vi_position, 1.0);
    gl_Position = vec4(vi_position, 1.0); //ui_projectionMatrix * ui_viewMatrix * worldPosition;
    fi_textureCoords = vi_textureCoords;
};
