#pragma once 

#include <stb_image.h>

class Texture {
public:
    Texture(const char* path, int offset);
    void bind();

private:

    int width, height, nrChannels, offset {};
    unsigned char *data;
    unsigned int ID;
};
