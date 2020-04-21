#version 330 core

uniform sampler2D ourTexture1;
in vec2 TexCoord;
out vec4 color;
void main()
{
 vec4 texcolor = texture(ourTexture1,vec2(TexCoord.x,1-TexCoord.y));
// if(texcolor.a < 0.1)
//	discard;
color = texcolor;
}