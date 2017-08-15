#version 330 core

in vec3 normal;
in vec2 uv;

uniform sampler2D texture_diffuse1;
//uniform sampler2D texture_specular1;
//uniform sampler2D texture_normal1;

out vec4 fragColor;

void main()
{
	vec4 texColor = texture(texture_diffuse1, uv);
	//vec4 texColor = texture(texture_specular1, uv);
	//vec4 texColor = texture(texture_normal1, uv);
	fragColor = vec4(texColor.rgb, 1.0);
}