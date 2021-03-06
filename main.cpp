#include <iostream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#if __EMSCRIPTEN__
#include "emscripten/bind.h"
#include "emscripten/emscripten.h"
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

struct dummy_data
{
    dummy_data(std::string k, int v) : key(k), value(v) {}
    int value;
    std::string key;
};

struct dummy_vector {
    dummy_vector() = default;
    dummy_vector(dummy_data d){
        vec.push_back(d);
    }

    void push(dummy_data d){
        vec.push_back(d);
    }
    dummy_data get(int index){
        return vec[index];
    }
    std::vector<dummy_data> vec{};
};

void isitup(){
    std::cout << "<<<<<<<<< si <<<<<<<<" << std::endl;
}

int gWidth;
int gHeight;

int EMSCRIPTEN_KEEPALIVE generate_rendition_using_idb(std::string input_image_path, std::string output_image_path)
{
    // load image
    int width, height, channels;
    unsigned char *img = stbi_load(input_image_path.c_str(), &width, &height, &channels, 0);

    if (img == NULL)
    {
        std::cout << "STB error loading: " << output_image_path << std::endl;
        return 2;
    }
    std::cout << "STB image loaded" << std::endl;

    std::cout << "STB write output to: " << output_image_path << std::endl;
    gWidth = width;
    gHeight = height;
    // return stbi_write_jpg(output_image_path.c_str(), width, height, channels, img, 100);
    // stbi_write_png_compression_level = 20;
    return stbi_write_png(output_image_path.c_str(), width, height, channels, img, 0);
}

int EMSCRIPTEN_KEEPALIVE get_width()
{
    return gWidth;
}

int EMSCRIPTEN_KEEPALIVE get_height()
{
    return gHeight;
}

#if __EMSCRIPTEN__
int EMSCRIPTEN_KEEPALIVE main(int argc, char *argv[])
{
    std::cout << "STB c++ has loaded" << std::endl;
}
EMSCRIPTEN_BINDINGS(generate_rendition_using_idb)
{
    emscripten::class_<dummy_data>("dummy_data")
        .constructor<std::string, int>()
        .property("key", &dummy_data::key)
        .property("value", &dummy_data::value);

    emscripten::class_<dummy_vector>("dummy_vector")
        .constructor<>()
        .constructor<dummy_data>()
        .function("push", &dummy_vector::push)
        .function("get", &dummy_vector::get);

    emscripten::function("generate_rendition_using_idb", &generate_rendition_using_idb);
    emscripten::function("get_width", &get_width);
    emscripten::function("get_height", &get_height);
    emscripten::function("isitup", &isitup);

    emscripten::register_vector<dummy_data>("vector<dummy_data>");
}
#else
int main(int argc, char* argv[]){
    std::cout << "STB c++ has loaded" << std::endl;
    if(argc < 3){
        std::cout << "STB usage: ./app input.psd output.png" << std::endl;
        return 1;
    }
    std::string input_image_path = std::string(argv[1]);
    std::string output_image_path = std::string(argv[2]);
    generate_rendition_using_idb(input_image_path, output_image_path);
    return 0; 
}
#endif //__EMSCRIPTEN__