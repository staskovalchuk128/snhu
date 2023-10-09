//Made this class based on LearnOpenGL article
//https://learnopengl.com/Getting-started/Textures

#pragma once
#include <vector>
#include <string>

class Texture2D
{
public:
    Texture2D(char const* path);
    void Bind(int index = 0) const;
    void Unbind();
private:
    unsigned int textureId;
    int width, height;
};
