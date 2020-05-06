#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;

//uniform vec3 albedo;
//uniform float metallic;
//uniform float roughness;
//uniform float ao;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;


uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;

const float PI = 3.14159265359;
vec3 getNormalFromMap()
{
  vec3 tangentNormal = texture(normalMap,TexCoords).xyz*2.0 - 1.0;
  vec3 Q1 = dFdx(WorldPos);
  vec3 Q2 = dFdy(WorldPos);
  vec2 st1 = dFdx(TexCoords);
  vec2 st2 = dFdy(TexCoords);

  vec3 N = normalize(Normal);
  vec3 T = normalize(Q1*st2.t - Q2*st1.t);
  vec3 B = -normalize(cross(N,T));
  mat3 TBN = mat3(T,B,N);
  return normalize(TBN *tangentNormal);
  }
float DistributionGGX(vec3 N,vec3 H,float roughness)
{
	float a = roughness * roughness;
	float a2 = a*a;
	float NdotH = max(dot(N,H),0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1)+1);
	denom = PI * denom * denom;
	return nom/max(denom,0.001f);

}

float GeometrySchlickGGX(float NdotV,float k)
{
	 float nom = NdotV;
	 float denom = NdotV *(1.0 - k)+k;
	 return nom/denom;
}
float GeometrySmith(vec3 N,vec3 V,vec3 L,float k)
{
	float NdotV = max(dot(N,V),0);
	float NdotL = max(dot(N,L),0);
	float ggx1 = GeometrySchlickGGX(NdotV,k);
	float ggx2 = GeometrySchlickGGX(NdotL,k);
	return ggx1 * ggx2;
}
//计算fresnel系数
vec3 fresnelSchlick(float cosTheta,vec3 F0)
{
	return F0+(1 - F0)*pow(1.0- cosTheta,5);
}
void main()
{
	vec3 albedo = pow(texture(albedoMap,TexCoords).rgb,vec3(2.2));
	float metallic = texture(metallicMap,TexCoords).r;
	float roughness = texture(roughnessMap,TexCoords).r;
	float ao = texture(aoMap,TexCoords).r;
	vec3 N = getNormalFromMap();
	vec3 V = normalize(camPos - WorldPos);
	vec3 F0 = vec3(0.04);
	F0 = mix(F0,albedo,metallic);

	//反射方程
	vec3 Lo = vec3(0);
	for(int i = 0;i<4;i++)
	{
		vec3 L = normalize(lightPositions[i] - WorldPos);
		vec3 H = normalize(V + L);

		float distan = length(lightPositions[i] - WorldPos);
		float attenuation = 1/(distan*distan);
		vec3 radiance = lightColors[i]* attenuation;

		//cook torrance
		float NDF = DistributionGGX(N,H,roughness);
		float G = GeometrySmith(N,V,L,roughness);
		vec3 F = fresnelSchlick(clamp(dot(H,V),0,1),F0);
		//分子

		vec3 nominator = NDF *G*F;
		//分母

		float denominator = 4 * max(dot(N,V),0)*max(dot(N,L),0);
		vec3 specular = nominator /max(denominator,0.001);

		vec3 KS = F;

		vec3 KD = vec3(1.0) - KS;

		KD *= 1.0 - metallic;
		float NdotL = max(dot(N,L),0);

		Lo += (KD*albedo/PI+specular)*radiance*NdotL;
	}
	vec3 ambient = vec3(0.03)*albedo*ao;
	vec3 color = ambient + Lo;
	//色调映射 hdr 
	color = color/(color+vec3(1));
	//gamma correct
	color = pow(color,vec3(1/2.2f));
	FragColor = vec4(color,1);
}