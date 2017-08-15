#version 330 core

in vec2 UV;

out vec4 fragColor;

uniform sampler2D Screen;

void main()
{
	vec4 frame = texture(Screen, UV);
    vec3 col = vec3(1.0) - frame.rgb;
    fragColor = vec4(col, frame.a);
} 