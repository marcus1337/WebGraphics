#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
uniform float aspect;
uniform float thickness;
out vec4 frag_color;


void main(){

    if(alpha == 0.0)
        discard;

    float maxX = 1.0 - thickness / aspect;
    float minX = thickness / aspect;
    float maxY = 1.0 - (thickness / aspect) * aspect;
    float minY = thickness / aspect;
    vec2 uv = uv_frag;
    minY *= aspect;

    if(uv.x > minX && uv.x < maxX && uv.y > minY && uv.y < maxY)
        discard;

    frag_color = vec4(color, alpha);  
}