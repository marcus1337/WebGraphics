#version 300 es

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;

uniform mat4 MVP;
uniform mat4 MV;

out vec2 uv_frag;
out vec3 vertPos;

void main(){
    uv_frag = uv;
    gl_Position = vec4(vertex, 1.0);
    gl_Position = MVP * gl_Position;

    vec4 vertPos4 = MV * vec4(vertex, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;
}