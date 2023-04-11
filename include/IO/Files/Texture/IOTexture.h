
#ifndef IOTEXTURE_H
#define IOTEXTURE_H
#include <GL/glew.h>
#include <vector>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>

struct TextureData {
    std::vector<unsigned char> data;
    unsigned width, height;
    std::string name;
};

class IOTexture
{
    std::vector<TextureData> textureDataVec;
    std::map<std::string, GLuint> loadedTextureHandles;
    void makeTexture(TextureData& textureData);

    TextureData getTextureData(std::string textureFilePath, std::string textureName);
    GLuint load2DTexture(const TextureData& textureData);
    void deleteTextures();

public:
    IOTexture();
    ~IOTexture();
    void loadTextures(std::vector<std::string> textureFilePaths, std::vector<std::string> textureNames);
    void loadIconImage(std::string filePath);
    GLuint getTexture(std::string name);
    GLFWimage iconImage;
};

#endif