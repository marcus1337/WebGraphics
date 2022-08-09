#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform sampler2D tex;
uniform sampler2D normalMap;
uniform vec2 inTexCoord;
uniform vec2 textureSize;
uniform float alpha;
uniform float isSingleColor;
uniform vec3 color;
uniform vec3 singleColor;
uniform float grayscale;
uniform float darken;
uniform float effect;
uniform vec2 mouse;

out vec4 frag_color;

vec3 greyscaleify(vec3 color, float str) {
    float g = dot(color, vec3(0.299, 0.587, 0.114));
    return mix(color, vec3(g), str);
}

void main(){

    vec2 realTexCoord = inTexCoord + (uv_frag * textureSize);
    frag_color = texture(tex, realTexCoord);

    if(frag_color.a == 0.0 || alpha == 0.0)
        discard;
    frag_color.a = min(alpha, frag_color.a);

    frag_color.xyz = frag_color.xyz * min(effect*effect, 0.7) + frag_color.xyz;
    frag_color = vec4(frag_color.xyz + color*effect, frag_color.a);
    //float mouseDist = distance(realTexCoord, mouse);
    //frag_color = vec4(frag_color.x  * mouseDist, frag_color.y, frag_color.z, frag_color.a);

    if(isSingleColor == 1.0){
        frag_color = vec4(singleColor, effect*0.1);
    }else if(grayscale == 1.0){
        vec3 gray = greyscaleify(frag_color.xyz, 1.0);
        frag_color = vec4(gray, alpha);
    }

}