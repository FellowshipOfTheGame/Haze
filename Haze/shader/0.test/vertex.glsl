#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out VS_OUT {
    vec2 uv;
} vs_out;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform mat4 NormalMatrix;

void main()
{
    vs_out.uv = uv;    
    gl_Position = Projection * View * Model * vec4(position, 1.0);
}