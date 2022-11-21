#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform sampler2D tex;
uniform vec2 inTexCoord;
uniform vec2 textureSize;
uniform float alpha;
uniform float image;
uniform vec3 color;
uniform vec3 defaultColor;
uniform float grayscale;
uniform float darken;

uniform float target;
uniform float highlight;
uniform float occupied;
uniform float check;
uniform float dark;

out vec4 frag_color;

float getDistance(){
    vec2 centerPos = vec2(0.5,0.5);
    vec2 uv = uv_frag;    
    return distance(centerPos, uv);
}

void main(){

    vec2 realTexCoord = inTexCoord + (uv_frag * textureSize);
    frag_color = texture(tex, realTexCoord);
    frag_color = vec4(frag_color.xyz + color, frag_color.a);

    if(frag_color.a == 0.0 || alpha == 0.0)
        discard;
    frag_color.a = min(alpha, frag_color.a);
    if(image == 0.0){
        frag_color = vec4(defaultColor, 1.0);
    }

    if(check == 1.0){
        frag_color.rgb = vec3(0.5,0.2,0.2) * 2.0 * (1.0 - getDistance());
    }

    vec3 highlightColor = vec3(0.5,0.5,0.4);
    if(highlight == 1.0 || (target == 1.0 && occupied == 1.0)){
        if(highlight == 1.0){
            highlightColor = vec3(0.5,0.5,0.4);
        }
        if(highlight == 1.0 && target == 1.0 && occupied == 1.0){
            highlightColor = vec3(0.1,0.5,0.1);
        }
        float dist = getDistance();
        if( dist > 0.6){
            frag_color.rgb = highlightColor * dist * 2.0;
        }
    }

    if(target == 1.0 && occupied == 0.0 && getDistance() < 0.12){
        float multiplier = (1.0 - getDistance())*1.4 ;
        frag_color.rgb = highlightColor * multiplier;
        frag_color.a = 1.0;
    }

    

}