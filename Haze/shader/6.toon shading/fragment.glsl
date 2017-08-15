#version 330 core

in VS_OUT {
	vec3 fragPos;
	vec3 normal;
    vec2 uv;
} vs_out;

uniform vec3 ViewPos;
uniform sampler2D texture_diffuse1;

const int slices = 3;
const float sliceSize = 1.0 / slices;

out vec4 fragColor;

void main()
{
	vec3 texDiffuse = texture(texture_diffuse1, vs_out.uv).rgb;
	
	
    vec3 norm = normalize(vs_out.normal);
    vec3 viewDir = normalize(ViewPos - vs_out.fragPos);
    float product = max(dot(norm, viewDir), 0.0);
	product = ceil(product * slices) / slices;
	
	if(product < 0.05)
		product = 0.0;
	
	
	vec3 result = product * vec3(0.5, 0.0, 0.5);
	//vec3 result = texDiffuse;
	
	fragColor = vec4(result, 1.0);
}