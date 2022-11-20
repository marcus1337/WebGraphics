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
const float maxBlur = 0.05;

out vec4 frag_color;


const vec3 lightPos = vec3(0.5, 0.5, 0.0);
const vec3 lightColor = vec3(1.0, 1.0, 1.0);
const float lightPower = 8.0;
const vec3 ambientColor = vec3(0.1, 0.1, 0.1);
const vec3 diffuseColor = vec3(1.0, 1.0, 1.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);
const float shininess = 12.0;
const float screenGamma = 2.2;

vec4 getLightEffect(vec3 normal){

    vec3 lightDir = lightPos - vertPos;
    float distance = length(lightDir);
    distance = distance * distance;
    lightDir = normalize(lightDir);

    float lambertian = max(dot(lightDir, normal), 0.0);
    float specular = 0.0;

     if (lambertian > 0.0) {
        vec3 viewDir = normalize(-vertPos);
        vec3 halfDir = normalize(lightDir + viewDir);
        float specAngle = max(dot(halfDir, normal), 0.0);
        specular = pow(specAngle, shininess);

        vec3 colorLinear = ambientColor +
                     diffuseColor * lambertian * lightColor * lightPower / distance +
                     specColor * specular * lightColor * lightPower / distance;
        vec3 colorGammaCorrected = pow(colorLinear, vec3(1.0 / screenGamma));
        return vec4(colorGammaCorrected, 1.0);

     }

    return vec4(ambientColor.rgb,1);
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

    if(usingNormalMap == 1.0){
        vec3 normal_color = texture(normalMap, realTexCoord).rgb;
        vec3 normal = 2.0 * normal_color - 1.0;
        vec4 color = getLightEffect(normal);
        frag_color = vec4(frag_color.rgb * color.rgb, frag_color.a);
    }


    if(effect != 0.0){

        float offset = effect * maxBlur;  
        vec2 offsets[9] = vec2[](
            vec2(-offset,  offset), // top-left
            vec2( 0.0f,    offset), // top-center
            vec2( offset,  offset), // top-right
            vec2(-offset,  0.0f),   // center-left
            vec2( 0.0f,    0.0f),   // center-center
            vec2( offset,  0.0f),   // center-right
            vec2(-offset, -offset), // bottom-left
            vec2( 0.0f,   -offset), // bottom-center
            vec2( offset, -offset)  // bottom-right    
        );
        float kernel[9] = float[](
            1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0,
            2.0 / 16.0, 4.0 / 16.0, 2.0 / 16.0,
            1.0 / 16.0, 2.0 / 16.0, 1.0 / 16.0  
        );

        vec3 sampleTex[9];
        for(int i = 0; i < 9; i++)
        {
            sampleTex[i] = vec3(texture(tex, realTexCoord + offsets[i]).xyz);
        }
        vec3 col = vec3(0.0);
        for(int i = 0; i < 9; i++)
            col += sampleTex[i] * kernel[i];
        frag_color = vec4(col, 1.0); 
    }

}