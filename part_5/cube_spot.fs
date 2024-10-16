

#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 color;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;  
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;
	
	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

	vec3 diffuse = vec3(0.0f, 0.0, 0.0);
	vec3 specular = vec3(0.0f, 0.0, 0.0);
	if (theta > light.outerCutOff) {

		float diff = max(dot(norm, lightDir), 0.0);
		diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
		
		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

		diffuse *= intensity;
		specular *= intensity * light.color;

	}

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
} 

