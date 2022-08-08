#version 300 es

precision highp float;

in vec2 TexCoords;
out vec4 frag_color;

uniform sampler2D text;
uniform vec3 color;
uniform float alpha;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    frag_color = vec4(color, alpha) * sampled;
}  