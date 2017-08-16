#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT
{
	vec2 uv;
	vec4 fragPos;
} vs_out[];

out VS_OUT{
	vec2 uv;
	vec4 fragPos;
} gs_out;

uniform float Time;

void main()
{
    gl_Position = gl_in[0].gl_Position;
	gl_Position.x += 0.2*sin(3.14*Time*vs_out[0].fragPos.z);
	gs_out.uv = vs_out[0].uv;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
	gl_Position.x += 0.2*sin(3.14*Time*vs_out[1].fragPos.z);
	gs_out.uv = vs_out[1].uv;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
	gl_Position.x += 0.2*sin(3.14*Time*vs_out[2].fragPos.z);
	gs_out.uv = vs_out[2].uv;
    EmitVertex();

    EndPrimitive();
}