#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out VS_OUT {
	vec3 fragPos;
	vec3 normal;
    vec2 uv;
} vs_out;


uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 NormalMatrix;

void main()
{  
    gl_Position = Projection * View * Model * vec4(a_position, 1.0);
	
	vs_out.fragPos = vec3(Model * vec4(a_position, 1.0));
	vs_out.normal = vec3(NormalMatrix *  vec4(a_normal, 1.0));
	vs_out.uv = a_uv;
}