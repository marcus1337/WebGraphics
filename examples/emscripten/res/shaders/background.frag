#version 300 es

precision highp float;

in vec2 uv_frag;
in vec3 vertPos;

uniform sampler2D tex;
uniform float alpha;
uniform vec3 color;
uniform float grayscale;
out vec4 frag_color;

void main(){
    frag_color = texture(tex, uv_frag);
    frag_color = vec4(frag_color.xyz + color, frag_color.a);

    if (grayscale == 1.0) {
        float gray = dot(frag_color.rgb, vec3(0.299, 0.587, 0.114));
        frag_color.rgb = vec3(gray);
    }

    if(frag_color.a == 0.0 || alpha == 0.0)
        discard;
    frag_color.a = min(alpha, frag_color.a);
}