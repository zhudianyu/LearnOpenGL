
#version 330 core
struct Material
{
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

uniform Material material;

struct Light
{
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

};
uniform Light light;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
  
    vec3 ambient = material.ambient * light.ambient;
 

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = (diff*material.diffuse) * light.diffuse;

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);

	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = (material.specular * spec) *light.specular;
	vec3 result = (diffuse + ambient + specular) ;
    color = vec4(result, 1.0f);

}