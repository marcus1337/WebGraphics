#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
out vec4 frag_color;


void main(){

    if(alpha == 0.0)
        discard;

    frag_color = vec4(color, alpha);
    

}