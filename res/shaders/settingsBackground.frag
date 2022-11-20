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

const int tileSize = 120;

int getTileSize(){
    return 120;
}

int getRow(float y){
    int numRows = 1080 / getTileSize();
    return int(float(numRows)*y);
}

int getCol(float x){
    int numCols = 1920 / getTileSize();
    return int(float(numCols)*x);
}

int isEvenRow(float y){
    return getRow(y) % 2;
}

int isEvenCol(float x){
    return getCol(x) % 2;
}

int isLightSquare(float x, float y){
    int result = 0;
    if(isEvenRow(y) == 1 && isEvenCol(x) == 0 ){
        result = 1;
    }
    if(isEvenRow(y) == 0 && isEvenCol(x) == 1 ){
        result = 1;
    }
    return result;
}

void main(){

    if(alpha == 0.0)
        discard;

    vec2 realTexCoord = inTexCoord + (uv_frag * textureSize);
    frag_color = texture(tex, realTexCoord);
    
    if(frag_color.a == 0.0)
        discard;
    if(alpha != 1.0)
        frag_color.a = alpha;

    if(isLightSquare(realTexCoord.x, realTexCoord.y) == 0 ){
        float multiplier = realTexCoord.y * realTexCoord.x;
        float r = frag_color.x - 0.5 * multiplier;
        float g = frag_color.y - 0.5 * multiplier;
        float b = frag_color.z - 0.5 * multiplier;
        frag_color = vec4(vec3(r, g, b), alpha); 
    }else{
        float multiplier = realTexCoord.y * realTexCoord.x;
        float r = frag_color.x - 0.5 * multiplier;
        float g = frag_color.y - 0.5 * multiplier;
        float b = frag_color.z - 0.5 * multiplier;
        frag_color = vec4(vec3(r, g, b), alpha); 
    }

}