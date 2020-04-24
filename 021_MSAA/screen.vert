#version 330 core
layout (location = 0) vec2 pos;
layout (location = 1) vec2 texCoords;
out vec2 TexCoords;
void main()
{
TexCoords = texCoords;
gl_Position = vec4(pos,0,1);
}