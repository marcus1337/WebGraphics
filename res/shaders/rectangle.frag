#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
uniform float aspect;
uniform float thickness;
out vec4 frag_color;

float getDistance(){
    float radius = 0.5;
    vec2 centerPos = vec2(0.5,0.5);
    vec2 uv = uv_frag;
    vec2 size = vec2(aspect, 1.0);
    vec2 pos = (abs(uv - centerPos) + centerPos) * size;
    return length(max(pos - size + radius, 0.0)) - radius;
}

void main(){

    if(alpha == 0.0)
        discard;

    vec3 _color = color;
    float _alpha = 1.0;
    if(getDistance() > 0.0)
        _alpha = 0.5;
    frag_color = vec4(_color, _alpha);  
}