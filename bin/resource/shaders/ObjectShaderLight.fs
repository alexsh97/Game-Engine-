#version 330 core
#define MAX_LIGHT 30

out vec4 FragmentColor;
//Struktura określiająca material obiektu
struct Material
{
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};
//Określa światło kierunkowe
struct DirectionLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//Światło punktowe
struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
//Strumień światła
struct SpotLight
{
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutOff;
	float outerCutOff;
};

//dane otrzymane z vertex shader
in vec3 outPos;
in vec3 outNormal;
in vec2 outTextureCoord;

//uniform sampler2D objectTexture;
uniform vec3 viewPos;

uniform Material material;

uniform DirectionLight dirLight;//światło kierunkowe
uniform PointLight pointLight[MAX_LIGHT];//punktowe
uniform int lightSize;
uniform SpotLight spotLight;//strumień światła

vec3 getDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection);
vec3 getPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir);
vec3 getSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDir);

void main()
{

	vec3 norm = normalize(outNormal);
	vec3 viewDir = normalize(viewPos - outPos);

	vec4 color = texture(material.diffuse, outTextureCoord);
	if(color.a < 0.1)
	{
		discard;
	}

	vec3 result = getDirectionLight(dirLight, norm, viewDir);

	for(int i = 0; i < lightSize; i++)
	{
        result += getPointLight(pointLight[i], norm, outPos, viewDir);
	}

	result += getSpotLight(spotLight, norm, outPos, viewDir);

    	FragmentColor = vec4(result, 1.0);
}

vec3 getDirectionLight(DirectionLight light, vec3 normal, vec3 viewDirection)
{
    vec3 lightDir = normalize(-light.direction);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), material.shininess);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * (spec * material.specular);
    return (ambient + diffuse + specular);
}

vec3 getPointLight(PointLight light, vec3 normal, vec3 position, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - position);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    float distance = length(light.position - position);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * (spec * material.specular);
   
    return (ambient + diffuse + specular);
}

vec3 getSpotLight(SpotLight light, vec3 normal, vec3 position, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - position);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   
    float distance = length(light.position - position);
    
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, outTextureCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, outTextureCoord));
    vec3 specular = light.specular * (spec * material.specular);
    ambient *=  intensity;
    diffuse *= intensity;
    specular *= intensity;
    return (ambient + diffuse + specular);
}

