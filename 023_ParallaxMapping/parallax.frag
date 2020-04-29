#version 330 core
out vec4 FragColor;

in VS_OUT {

	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
	}fs_in;

	uniform sampler2D diffuseMap;
	uniform sampler2D normalMap;
	uniform sampler2D depthMap;

	uniform float hight_Scale;

	vec2 ParallaxMapping(vec2 texCoords,vec3 viewDir)
	{
		float height = texture(depthMap,texCoords).r;
		return texCoords - viewDir.xy/viewDir.z*(height *hight_Scale);
	}

	void main()
	{
		vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
		vec2 texCoords = ParallaxMapping(fs_in.TexCoords,viewDir);

		vec3 diffuse = texture(diffuseMap,texCoords).rgb;
		vec3 normal = texture(normalMap,texCoords).rgb;
		vec3 ambient = 0.1f*diffuse;
		normal = normalize(normal*2.0 - 1.0);

		vec3 lightDir = normalize(fs_in.TangentLightPos - fs_in.TangentFragPos);
		float diff = max(dot(lightDir,normal),0);
		vec3 diffusecolor = diff* diffuse;

		vec3 reflectDir = reflect(-lightDir,normal);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(normal,halfwayDir),0),32);
		vec3 specalur = vec3(0.2)*spec;
		FragColor = vec4(ambient+diffuse+specalur,1.0);

	}
