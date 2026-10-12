#pragma once

#include <stb_image.h>

#include <string>
#include <sstream>
#include <fstream>


class AssetManager {
  public:
    static std::string load_txt_file(const char* path);
    static unsigned char* load_texture_file(const char* path, int* width, int* height, int* nrChannels);
    static void image_free(unsigned char* data);
  private:
};
