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

    vec2 uv = uv_frag * 2.0 - 1.0;

    frag_color = vec4(color, alpha);

    float distance = 1.0 - length(uv);
    if(distance > 0.0)
        distance = 1.0;
    
    frag_color.rgb = vec3(distance);
    

}