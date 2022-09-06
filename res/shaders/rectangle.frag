#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
uniform float aspect;
uniform float thickness;
out vec4 frag_color;

float getDistance(float radius){
    vec2 centerPos = vec2(0.5,0.5);
    vec2 size = vec2(500,250);
    vec2 pos = (abs(uv_frag - centerPos) + 0.5) * size;
    return length(max(pos - (size - radius), 0.0));
}

void main(){

    if(alpha == 0.0)
        discard;

    float maxX = 1.0 - thickness / aspect;
    float minX = thickness / aspect;
    float maxY = 1.0 - thickness;
    float minY = thickness;
    vec2 uv = uv_frag;

    float radius = 60.0;
    float distLimit = 50.0;
    float distance = getDistance(radius);
    
    //if(uv.x > minX && uv.x < maxX && uv.y > minY && uv.y < maxY)
    //    discard;
    vec3 _color = color;
    if(distance > distLimit)
        _color = vec3(0.0,distance,0.0);
    frag_color = vec4(_color, alpha);  
}