#pragma once


#include <GL\glew.h>
#include <string>

enum TextureType
{
    Diffuse,
    Specular

};


class Texture
{
public:
    Texture();
    ~Texture();

    bool load(const std::string &file_);
    void unload();

    void bind();
        void unbind();


private:

    GLuint texObj = 0;
};

