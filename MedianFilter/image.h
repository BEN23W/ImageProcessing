#include<stdint.h>
#include<cstdio>

#define STEG_HEADER_SIZE sizeof(uint32_t)*8

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
    Image& colorMask(float r, float g, float b);
    Image& encodeMessage(const char* message);
    Image& decodeMessage(char* buffer, size_t* messageLength);
    Image& diffmap(Image& img);

};