#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
uniform float width;
uniform float height;
uniform float aspect;
uniform float thickness;
out vec4 frag_color;


vec2 getAspectRatio(){
    vec2 aspectRatio = vec2(1.0, 1.0);
    if(width > height)
        aspectRatio.x = width/height;
    else if(height > width)
        aspectRatio.y = height/width;
    return aspectRatio; 
}

float getDistance(float _thickness){
    float radius = 0.2;
    vec2 centerPos = vec2(0.5,0.5);
    vec2 uv = uv_frag;    
    vec2 size = getAspectRatio();
    vec2 pos = (abs(uv - centerPos) + centerPos) * size;
    return length(max(pos - size + radius*(1.0+_thickness), 0.0)) - radius;
}

void main(){

    if(alpha == 0.0)
        discard;

    vec3 _color = color;
    float _alpha = alpha;
    float distance1 = getDistance(0.0);
    float distance2 = getDistance(thickness);
    if(distance1 > 0.0 || distance2 < 0.0)
        _alpha = 0.0;
    frag_color = vec4(_color, _alpha);  
}