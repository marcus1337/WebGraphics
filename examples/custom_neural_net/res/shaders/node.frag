#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform sampler2D tex;
uniform vec2 inTexCoord;
uniform vec2 texSize;
uniform float alpha;
uniform float image;
uniform vec3 color;
uniform vec3 defaultColor;
uniform float grayscale;
uniform float darken;

out vec4 frag_color;

float getDistance(){
    vec2 centerPos = vec2(0.5,0.5);
    vec2 uv = uv_frag;    
    return distance(centerPos, uv);
}

void main(){

    frag_color = vec4(0.0, 0.0, 0.0, alpha);
    float distance = getDistance();
    if(distance > 0.5){
        discard;
    }

}