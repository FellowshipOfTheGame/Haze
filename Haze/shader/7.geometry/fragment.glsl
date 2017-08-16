#version 330 core

in VS_OUT{
	vec2 uv;
	vec4 fragPos;
} gs_out;

uniform sampler2D texture_diffuse1;

out vec4 fragColor;

void main()
{
	vec4 texColor = texture(texture_diffuse1, gs_out.uv);
	fragColor = vec4(texColor.rgb, 1.0);
}