#version 300 es

precision highp float;

uniform sampler2D tex;

uniform float useTexture;
out vec4 frag_color;
in vec3 v_normal;
in vec2 frag_uv_coord;

void main()
{
	vec3 N = normalize(v_normal);
	vec4 N_color = vec4(0.5 * N + 0.5, 1.0);
	frag_color = N_color;
	if(useTexture == 1.0){
		frag_color = texture(tex, frag_uv_coord);
	}
	frag_color = vec4(1.0,0.0,0.0,1.0);
	
}