#version 330 core

in VS_OUT {
	vec3 fragPos;
	vec3 normal;
    vec2 uv;
} vs_out;

uniform vec3 ViewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

const vec3 lightPosition = vec3(5.0, 5.0, 1.0);
const vec3 lightDirection = vec3(-0.2, -1.0, -0.3);

const vec3 lightColorAmbient = vec3(0.1, 0.1, 0.1);
const vec3 lightColorDiffuse = vec3(1.0, 1.0, 1.0);
const vec3 lightColorSpecular = vec3(1.0, 1.0, 1.0);

const float lightShininess = 64.0;

const float directionalIntensity = 0.25;

struct LightAttenuation
{
	float constant;
	float linear;
	float quadratic;
};

uniform LightAttenuation Attenuation;

//#define MAX_LIGHTS 8
//uniform Light lights[MAX_LIGHTS];

out vec4 fragColor;

void main()
{
	vec3 texDiffuse = texture(texture_diffuse1, vs_out.uv).rgb;
	vec3 texSpecular = texture(texture_specular1, vs_out.uv).rgb;
	
	
    // Ambient
    vec3 ambient = lightColorAmbient * texDiffuse;
  	
    // Directional Diffuse 
    vec3 norm = normalize(vs_out.normal);
    vec3 lightDir = normalize(-lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColorDiffuse * texDiffuse;  
    
    // Directional Specular
    vec3 viewDir = normalize(ViewPos - vs_out.fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), lightShininess);
    vec3 specular = spec * lightColorSpecular * texSpecular;
    
    vec3 directional = diffuse + specular;
	
	
	// Point Diffuse
    lightDir = normalize(lightPosition - vs_out.fragPos);
    diff = max(dot(norm, lightDir), 0.0);
    diffuse = lightColorDiffuse * diff * texDiffuse;
    
    // Point Specular
    viewDir = normalize(ViewPos - vs_out.fragPos);
    reflectDir = reflect(-lightDir, norm);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), lightShininess);
    specular = lightColorSpecular * spec * texSpecular;
    
    // Attenuation
    float distance    = length(lightPosition - vs_out.fragPos);
    float attenuation = 1.0 / (Attenuation.constant + Attenuation.linear * distance + Attenuation.quadratic * (distance * distance));
	
	vec3 point = attenuation * (diffuse + specular);
	
	// Final Result
	vec3 result = ambient + directionalIntensity * directional + point;
	
	fragColor = vec4(result, 1.0);
}