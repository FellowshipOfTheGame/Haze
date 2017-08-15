#version 330 core

in VS_OUT {
	vec3 fragPos;
	vec3 normal;
    vec2 uv;
} vs_out;

uniform vec3 ViewPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

const vec3 lightDir = vec3(-0.2, -1.0, -0.3);

const vec3 lightColorAmbient = vec3(0.1, 0.1, 0.1);
const vec3 lightColorDiffuse = vec3(1.0, 1.0, 1.0);
const vec3 lightColorSpecular = vec3(1.0, 1.0, 1.0);

const float lightShininess = 64.0;

out vec4 fragColor;

void main()
{
	vec3 texDiffuse = texture(texture_diffuse1, vs_out.uv).rgb;
	vec3 texSpecular = texture(texture_specular1, vs_out.uv).rgb;
	
	
    // Ambient
    vec3 ambient = lightColorAmbient * texDiffuse;
  	
    // Diffuse 
    vec3 norm = normalize(vs_out.normal);
    vec3 lightDir = normalize(-lightDir);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColorDiffuse * texDiffuse;  
    
    // Specular
    vec3 viewDir = normalize(ViewPos - vs_out.fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), lightShininess);
    vec3 specular = spec * lightColorSpecular * texSpecular;  
        
    vec3 result = ambient + diffuse + specular;
	
	fragColor = vec4(result, 1.0);
}