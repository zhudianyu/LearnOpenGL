
#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;
 

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (diffuse + ambient) * objectColor;
    color = vec4(result, 1.0f);

}