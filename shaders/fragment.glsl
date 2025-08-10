#version 330

varying vec3 fi_color;

void main()
{
    gl_FragColor = vec4(fi_color, 1.0);  
};
