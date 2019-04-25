#version 440 core
out vec4 vertColour;

struct DirectLight
{
	vec3 direction;
	vec3 colour;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	float constant;
	float linear;
	float quadratic;
};

in vec3 vs_col;
in vec3 vs_nor;
in vec2 vs_uv;
in vec4 vs_pos;

uniform int renderType;
uniform sampler2D aTex;
uniform vec3 shapeColour;
uniform float colorModifier;
uniform vec3 viewPos;

#define MAX_NUMBER_LIGHTS 3
uniform PointLight pLights[MAX_NUMBER_LIGHTS];
uniform DirectLight dLight;

vec3 CalculateDirectionalLighting(vec4 sampled, DirectLight light, vec3 norm, vec3 viewDir)
{
	vec3 ambient = (light.colour * sampled.rgb);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.colour * diff * sampled.rgb;
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	vec3 specular = vec3(0.1f) * spec * sampled.rgb;
	return (ambient + specular + diffuse);
}

vec3 CalculatePointLighting(vec4 sampled, PointLight light, vec3 norm, vec3 vs_pos, vec3 viewDir)
{
	vec3 ambient = (light.ambient * sampled.rgb);
	vec3 lightDir = normalize(light.position.xyz - vs_pos.xyz);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * sampled.rgb;
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	vec3 specular = vec3(0.1f) * spec * sampled.rgb;
    float distance = length(light.position - vs_pos.xyz);
    float atten = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

	ambient  *= atten;  
    diffuse   *= atten;
    specular *= atten;  
	return (ambient + diffuse + specular);
}

void main()
{	
	vec4 sampled = vec4(1.0f);
	if(renderType == 0) //TEXTURE
	{
		sampled = texture(aTex, vs_uv);
	}
	else if(renderType == 1) //VERTEX_COLOUR
	{
		sampled = vec4(vs_col, 1.0f);
	}
	else if(renderType == 2) //COLOUR
	{
		sampled = vec4(shapeColour, 1.0f);
	}
	else if(renderType == 3) //SPECIAL_BUBBLE
	{
		float r = clamp(shapeColour.r + sin(vs_pos.x) + sin(vs_pos.y), 0.25f, 1.0f);
		float g = clamp(shapeColour.g + sin(vs_pos.y) + sin(vs_pos.x), 0.25f, 1.0f);
		vec4 texAlpha = texture(aTex, vs_uv);
		sampled = vec4(r, g, shapeColour.b, texAlpha.w);
	}

	vec3 normal = normalize(vs_nor);
	vec3 viewDirection = normalize(viewPos - vs_pos.xyz);

	vec3 result = CalculateDirectionalLighting(sampled, dLight, normal, viewDirection);

	for(int i = 0;  i < MAX_NUMBER_LIGHTS; i++)
		result += CalculatePointLighting(sampled, pLights[i], normal, vs_pos.xyz, viewDirection);

	//vertColour = sampled;
	vertColour = vec4(result.x, result.y, result.z, sampled.w);
} 	