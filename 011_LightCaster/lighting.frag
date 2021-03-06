
#version 330 core
struct Material
{
   vec3 ambient;
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

uniform Material material;

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
uniform Light light;
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
out vec4 color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
void main()
{
  
    vec3 ambient =light.ambient * vec3(texture(material.diffuse,TexCoords));
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = (diff*vec3(texture(material.diffuse,TexCoords))) * light.diffuse;

	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir,norm);

	float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
	vec3 specular = (vec3(texture(material.specular,TexCoords)) * spec) *light.specular;

	float distance = length(light.position - FragPos);
	float attenuation = 1.0f/(light.constant + light.linear*distance+light.quadratic*(distance*distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	vec3 result = (diffuse + ambient + specular) ;
    color = vec4(result, 1.0f);

}