#include "IO/Files/Shader/DefaultShaderCode.h"
#include <GL/glew.h>

ShaderCode DefaultShaderCode::getDefault2DVertexCode() {
    ShaderCode default2DVertexCode;
    default2DVertexCode.shaderType = GL_VERTEX_SHADER;
    default2DVertexCode.glslCode = R"(#version 300 es

        layout (location = 0) in vec3 vertex;
        layout (location = 1) in vec2 uv;

        uniform mat4 MVP;
        uniform mat4 MV;

        out vec2 uv_frag;
        out vec3 vertPos;

        void main(){
            uv_frag = uv;
            gl_Position = vec4(vertex, 1.0);
            gl_Position = MVP * gl_Position;

            vec4 vertPos4 = MV * vec4(vertex, 1.0);
            vertPos = vec3(vertPos4) / vertPos4.w;
        }
    )";

    return default2DVertexCode;
}

std::vector<ShaderCode> DefaultShaderCode::getImageCode() {
    ShaderCode imageFragCode;
    imageFragCode.shaderType = GL_FRAGMENT_SHADER;

    imageFragCode.glslCode = R"(#version 300 es

        precision highp float;
        in vec2 uv_frag;
        in vec3 vertPos;

        uniform sampler2D tex;
        uniform float alpha;
        uniform vec3 color;
        uniform float grayscale;

        out vec4 frag_color;

        vec3 greyscaleify(vec3 color, float str) {
            float g = dot(color, vec3(0.299, 0.587, 0.114));
            return mix(color, vec3(g), str);
        }

        void main(){
            frag_color = texture(tex, uv_frag);
            frag_color = vec4(frag_color.xyz + color, frag_color.a);

            if(frag_color.a == 0.0 || alpha == 0.0)
                discard;
            frag_color.a = min(alpha, frag_color.a);

            if(grayscale == 1.0){
                vec3 gray = greyscaleify(frag_color.xyz, 1.0);
                frag_color = vec4(gray, alpha);
            }

        }
    )";

    return { getDefault2DVertexCode(), imageFragCode };
}

std::vector<ShaderCode> DefaultShaderCode::getRectangleCode() {
    ShaderCode rectangleFragCode;
    rectangleFragCode.shaderType = GL_FRAGMENT_SHADER;

    rectangleFragCode.glslCode = R"(#version 300 es

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
    )";

    return { getDefault2DVertexCode(), rectangleFragCode };
}

std::vector<ShaderCode> DefaultShaderCode::getTextCode() {
    ShaderCode textVertexCode, textFragmentCode;
    textFragmentCode.shaderType = GL_FRAGMENT_SHADER;
    textVertexCode.shaderType = GL_VERTEX_SHADER;

    textFragmentCode.glslCode = R"(#version 300 es

        precision highp float;

        in vec2 TexCoords;
        out vec4 frag_color;

        uniform sampler2D text;
        uniform vec3 color;
        uniform float alpha;

        void main()
        {    
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
            frag_color = vec4(color, alpha) * sampled;
        }  
    )";

    textVertexCode.glslCode = R"(#version 300 es

        layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
        out vec2 TexCoords;

        uniform mat4 MVP;

        void main()
        {
            gl_Position = MVP * vec4( vec3(vertex.xy, 0.0), 1.0);
            TexCoords = vertex.zw;
        }  
    )";

    return { textVertexCode , textFragmentCode };
}

std::vector<ShaderCode> DefaultShaderCode::getModelCode() {
    ShaderCode vertexCode, fragmentCode;
    fragmentCode.shaderType = GL_FRAGMENT_SHADER;
    vertexCode.shaderType = GL_VERTEX_SHADER;

    fragmentCode.glslCode = R"(#version 300 es

    precision highp float;

    uniform sampler2D tex;
    uniform float useTexture;

    out vec4 frag_color;
    in vec3 v_normal;
    in vec2 frag_uv_coord;

    void main()
    {
	    frag_color = vec4(0.5,0.5,0.0,1.0);
	    vec3 N = normalize(v_normal);
	    vec4 N_color = vec4(0.5 * N + 0.5, 1.0);
	    frag_color = N_color;
	    if(useTexture == 1.0){
		    frag_color = texture(tex, frag_uv_coord);
	    }
	
    }
    )";

    vertexCode.glslCode = R"(#version 300 es
    layout (location = 0) in vec3 position;
    layout (location = 1) in vec3 a_normal;
    layout (location = 2) in vec2 uv_coord;

    uniform mat4 MVP;
    out vec3 v_normal;
    out vec2 frag_uv_coord;

    void main()
    {
	    v_normal = a_normal;
	    frag_uv_coord = uv_coord;
	    gl_Position = vec4(position.x, position.y, position.z, 1.0);
	    gl_Position = MVP * gl_Position;
    }
    )";

    return { vertexCode, fragmentCode };
}