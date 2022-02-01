#include<stdint.h>
#include<cstdio>


enum ImageType {
	PNG, JPG, BMP, TGA
};

struct Image{
    uint8_t* data = NULL; //unsigned int 8 bytes
    size_t size = 0; //
    int width;
    int height;
    int channels;

    Image(const char* filename, int channel_force=0);
    Image(int width, int height, int channels);
    Image(const Image& img);
    ~Image();

    bool read(const char* filename, int channel_force = 0);
    bool write(const char* filename);
    ImageType get_file_type(const char* filename);
    Image& grayscale_avg();
    Image& grayscale_lumins();
};