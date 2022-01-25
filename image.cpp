#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"

#include<iostream>
#include<fstream>
#include<sstream>



    Image::Image(const char* filename){
        if(read(filename)){
            printf("Read %s\n", filname);
            size = width*height*channels;
        }
        else{
            printf("Failed to read image %s\n", filename);
        }
    }
    Image::Image(int width, int height, int channels): width(width), height(height), channels(channels){
        size = width*height*channels;
        data = new uint8_t[size];

    }
    Image::Image(cont Image& img){

    }
    Image::~Image(){
        stbi_image_free(data)
    }
    bool Image::read(const char* filename){
        stbi_load(filename, &width, &height, &channels, 0);
        return data != NULL;
    }
    bool Image::write(const char* filename){

    }


