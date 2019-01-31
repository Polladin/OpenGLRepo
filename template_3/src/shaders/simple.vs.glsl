#version 420 core                                               
                                                              
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main(void) 
{
  gl_Position = vec4(aPos, 1.0);
  TexCoord = vec2(1.0f, 1.0f) - ( vec2(aPos.x, aPos.y) + vec2(1.0, 1.0) ) / 2;
}                   