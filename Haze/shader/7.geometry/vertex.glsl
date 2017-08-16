#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 2) in vec2 a_uv;

out VS_OUT
{
	vec2 uv;
	vec4 fragPos;
} vs_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{  
    gl_Position = Projection * View * Model * vec4(a_position, 1.0);
	vs_out.uv = a_uv;
	vs_out.fragPos = Model * vec4(a_position, 1.0);
}