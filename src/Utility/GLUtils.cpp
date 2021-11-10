
#include "GLUtils.h"

std::string GLUtils::readShaderSource(const std::string &filename)
{
    std::ifstream file(filename);
    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

void GLUtils::showShaderInfoLog(GLuint shader)
{
    GLint infoLogLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetShaderInfoLog(shader, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

void GLUtils::showProgramInfoLog(GLuint program)
{
    GLint infoLogLength = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
    std::vector<char> infoLog(infoLogLength);
    glGetProgramInfoLog(program, infoLogLength, &infoLogLength, &infoLog[0]);
    std::string infoLogStr(infoLog.begin(), infoLog.end());
    std::cerr << infoLogStr << std::endl;
}

bool GLUtils::wasShaderCompiled(GLuint shader)
{
    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        std::clog << "Shader compilation failed, " << shader << std::endl;
        showShaderInfoLog(shader);
    }
    return compiled != 0;
}

GLuint GLUtils::linkProgram(std::vector<GLuint> shaders)
{
    GLuint program = glCreateProgram();

    for (GLuint shader : shaders)
    {
        glAttachShader(program, shader);
    }
    glLinkProgram(program);

    GLint linked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);
    if (!linked)
    {
        std::cerr << "Program linking failed, " << program << std::endl;
        showProgramInfoLog(program);
        glDeleteProgram(program);
    }

    for (GLuint shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    if (!linked)
        return 0;

    return program;
}

GLuint GLUtils::compileShader(const std::string &shaderFilename, std::string &shaderFilePath, uint32_t shaderType){
    GLuint shader = glCreateShader(shaderType);
    std::string vertexShaderSource = GLUtils::readShaderSource(shaderFilePath + shaderFilename);
    const char *shaderSourcePtr = vertexShaderSource.c_str();
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shader);
    return shader;
}

GLuint GLUtils::loadShaderProgram(const std::string &vertexShaderFilename,
                                  const std::string &fragmentShaderFilename, std::string &shaderFilePath)
{
    GLuint vertexShader = compileShader(vertexShaderFilename, shaderFilePath, GL_VERTEX_SHADER);

    if (!wasShaderCompiled(vertexShader))
    {
        glDeleteShader(vertexShader);
        return 0;
    }

    GLuint fragmentShader = compileShader(fragmentShaderFilename, shaderFilePath, GL_FRAGMENT_SHADER);

    if (!wasShaderCompiled(fragmentShader))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return 0;
    }

    return linkProgram({vertexShader, fragmentShader});
}

GLFWimage GLUtils::loadIconImage(std::string &imagePath)
{
    unsigned error;
    GLFWimage image;
    error = lodepng_decode32_file(&(image.pixels), (unsigned int *)&(image.width), (unsigned int *)&(image.height), imagePath.c_str());
    if (error)
        printf("error %u: %s\n", error, lodepng_error_text(error));
    return image;
}

GLuint GLUtils::load2DTexture(const std::string &filename_, std::string &textureFilePath)
{
    std::string filename = textureFilePath + filename_;
    std::vector<unsigned char> data;
    unsigned width, height;
    unsigned error = lodepng::decode(data, width, height, filename);
    if (error != 0)
    {
        std::clog << "Error: " << lodepng_error_text(error) << std::endl;
        std::exit(EXIT_FAILURE);
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, &(data[0]));

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}