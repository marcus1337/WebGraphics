#version 300 es

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 uv_coord;

uniform mat4 MVP;
out vec3 v_normal;
out vec2 frag_uv_coord;

void main()
{
	v_normal = a_normal;
	frag_uv_coord = uv_coord;

	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	gl_Position = MVP * gl_Position;

}