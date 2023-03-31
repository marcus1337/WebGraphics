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
        uniform sampler2D normalMap;
        uniform vec2 inTexCoord;
        uniform vec2 texSize;
        uniform float alpha;
        uniform float image;
        uniform vec3 color;
        uniform vec3 defaultColor;
        uniform float grayscale;
        uniform float darken;

        uniform float effect;

        out vec4 frag_color;

        vec3 greyscaleify(vec3 color, float str) {
            float g = dot(color, vec3(0.299, 0.587, 0.114));
            return mix(color, vec3(g), str);
        }

        void applyButtonEffect(){
            if(effect == 0.0)
            {
                return;
            }
            frag_color.xyz = frag_color.xyz * min(effect*effect, 0.7) + frag_color.xyz;
        }

        void main(){

            vec2 realTexCoord = inTexCoord + (uv_frag * texSize);
            frag_color = texture(tex, realTexCoord);
            frag_color = vec4(frag_color.xyz + color, frag_color.a);

            if(frag_color.a == 0.0 || alpha == 0.0)
                discard;
            frag_color.a = min(alpha, frag_color.a);

            if(image == 0.0){
                frag_color = vec4(defaultColor, 1.0);
            }else if(grayscale == 1.0){
                vec3 gray = greyscaleify(frag_color.xyz, 1.0);
                frag_color = vec4(gray, alpha);
            }
            applyButtonEffect();

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
        uniform float width;
        uniform float height;
        uniform float radius;
        uniform float aspect;
        uniform float thickness;
        out vec4 frag_color;


        vec2 getAspectRatio(){
            vec2 aspectRatio = vec2(1.0, 1.0);
            if(width > height)
                aspectRatio.x = width/height;
            else if(height > width)
                aspectRatio.y = height/width;
            return aspectRatio; 
        }

        float getDistance(){
            vec2 centerPos = vec2(0.5,0.5);
            vec2 uv = uv_frag;    
            vec2 size = getAspectRatio();
            vec2 pos = (abs(uv - centerPos) + centerPos) * size;
            return length(max(pos - size + radius, 0.0)) - radius;
        }

        void main(){

            if(alpha == 0.0)
                discard;

            vec3 _color = color;
            float _alpha = alpha;
            float distance = getDistance();
            if(distance > 0.0 || distance < -(thickness*aspect))
                _alpha = 0.0;
            frag_color = vec4(_color, _alpha);  
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

