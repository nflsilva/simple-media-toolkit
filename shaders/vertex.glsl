#version 400 core

layout (location = 0) in vec3 vi_position;
layout (location = 1) in vec2 vi_textureCoords;
layout (location = 2) in float vi_textureIndex;

uniform mat4 uni_modelMatrix;
uniform mat4 uni_viewMatrix;
uniform mat4 uni_projectionMatrix;

out vec2 fi_textureCoords;
flat out int fi_textureIndex;

void main()
{
    vec4 worldPosition = vec4(vi_position, 1.0);
    gl_Position = uni_projectionMatrix * worldPosition;
    fi_textureCoords = vi_textureCoords;
    fi_textureIndex = int(vi_textureIndex);
};