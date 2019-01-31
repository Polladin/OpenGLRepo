#version 420 core 

out vec4 color;

uniform vec4 color_in;    

void main(void) 
{
    color = color_in;
}                              