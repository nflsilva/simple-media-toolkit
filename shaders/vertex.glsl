#version 400 core

layout (location = 0) in vec3 vi_position;
layout (location = 1) in vec2 vi_textureCoords;
layout (location = 2) in float vi_textureIndex;
layout (location = 3) in vec3 vi_translation;
layout (location = 4) in vec2 vi_scaling;
layout (location = 5) in float vi_rotation;

uniform mat4 uni_viewMatrix;
uniform mat4 uni_projectionMatrix;

out vec2 fi_textureCoords;
flat out int fi_textureIndex;

mat4 createModelMatrix() {
    // Rotation matrix
    mat4 rotationMatrix = mat4(
        cos(vi_rotation),  -sin(vi_rotation),   0.0,    0.0,
        sin(vi_rotation),   cos(vi_rotation),   0.0,    0.0,
        0.0,                0.0,                1.0,    0.0,
        0.0,                0.0,                0.0,    1.0
    );

    // Scaling matrix
    mat4 scaleMatrix = mat4(
        vi_scaling.x,       0.0,                0.0,    0.0,
        0.0,                vi_scaling.y,       0.0,    0.0,
        0.0,                0.0,                1.0,    0.0,
        0.0,                0.0,                0.0,    1.0
    );

    // Translation matrix
    mat4 translationMatrix = mat4(
        1.0,                0.0,                0.0,    vi_translation.x,
        0.0,                1.0,                0.0,    vi_translation.y,
        0.0,                0.0,                1.0,    vi_translation.z,
        0.0,                0.0,                0.0,    1.0
    );

    return transpose(translationMatrix * rotationMatrix * scaleMatrix);
}

void main()
{
    mat4 modelMatrix = createModelMatrix();
    vec4 worldPosition = modelMatrix * vec4(vi_position, 1.0);

    gl_Position = uni_projectionMatrix * uni_viewMatrix * worldPosition;
    fi_textureCoords = vi_textureCoords;
    fi_textureIndex = int(vi_textureIndex);
};