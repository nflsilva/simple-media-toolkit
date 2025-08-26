#version 400 core

in vec2 fi_textureCoords;
flat in int fi_textureIndex;

uniform sampler2D uni_textures[16];

void main()
{
    vec4 color = texture(uni_textures[fi_textureIndex], fi_textureCoords);
    if(color.a == 0) {
        discard;
    }
    gl_FragColor = color;
};