#version 330 core

in vec2 TexCoord;
out vec4 color;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

float LinearizeDepth(float depth)
{
	float near = 1;
	float far = 100;
	float z = depth *2 - 1;
	return (2.0*near)/(far+near - z * (far - near));
}
void main()
{
	//color = mix(texture(ourTexture1,TexCoord),texture(ourTexture2,vec2(1-TexCoord.x,1-TexCoord.y)),0.2);
	//color = vec4(vec3(gl_FragCoord.z),1.0f);
	float depth = LinearizeDepth(gl_FragCoord.z);
	color = vec4(vec3(depth),1.0f);
	
}