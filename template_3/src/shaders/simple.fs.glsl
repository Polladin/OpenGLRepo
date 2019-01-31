#version 420 core                                                
                                                                 
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture;

void main(void) 
{
	FragColor = texture(texture, TexCoord);
}                              