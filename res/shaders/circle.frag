#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform vec3 color;
uniform float alpha;
uniform float thickness;
uniform float fade;
out vec4 frag_color;


void main(){

    if(alpha == 0.0)
        discard;

    vec2 uv = uv_frag * 2.0 - 1.0;
    frag_color = vec4(color, alpha);

    float distance = 1.0 - length(uv);
    vec3 colorIntensity = vec3(smoothstep(0.0, fade, distance));
    vec3 ringColorIntensity = vec3(1.0);

    if(thickness < 1.0)
        ringColorIntensity = vec3(1.0 - smoothstep(thickness - fade, thickness, distance));
    if(distance < 0.0 || length(ringColorIntensity) <= 0.0)
        discard; 
    
    frag_color.rgb = colorIntensity * ringColorIntensity * color;

}
