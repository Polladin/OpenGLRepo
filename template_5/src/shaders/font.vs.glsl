#version 420 core                                               

layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = vec4(vertex.x, vertex.y, 0.0, 1.0); //projection *
    TexCoords = vec2(vertex.z, 1.0 - vertex.w);
}                                   