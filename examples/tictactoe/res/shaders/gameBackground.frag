#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform sampler2D tex;
uniform sampler2D normalMap;

uniform vec2 inTexCoord;
uniform vec2 textureSize;
uniform float alpha;
uniform float usingNormalMap;

uniform float effect;

out vec4 frag_color;


void main(){

    if(alpha == 0.0)
        discard;

    vec2 realTexCoord = inTexCoord + (uv_frag * textureSize);
    frag_color = texture(tex, realTexCoord);
    
    if(frag_color.a == 0.0)
        discard;
    if(alpha != 1.0)
        frag_color.a = alpha;

    frag_color.rgb = vec3(0.2,0.2,0.2) * length(realTexCoord);
    

}