#version 330 core

in vec2 UV;

out vec4 fragColor;

uniform sampler2D texture_framebuffer;

void main()
{
    vec3 col = vec3(1) - texture(texture_framebuffer, UV).rgb;
    fragColor = vec4(col, 1.0);
} 