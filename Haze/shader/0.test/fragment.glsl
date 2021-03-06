#version 330 core

in VS_OUT {
	vec2 uv;
} vs_out;

out vec4 fragColor;

uniform sampler2D texture_diffuse1;

void main()
{    
    fragColor = texture(texture_diffuse1, vs_out.uv);
	fragColor.a = 1.0;
}