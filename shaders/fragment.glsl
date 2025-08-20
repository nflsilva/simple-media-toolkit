#version 330 core

in vec2 fi_textureCoords;

uniform sampler2D uni_sprite;

void main()
{
    gl_FragColor = texture(uni_sprite, fi_textureCoords);  
};