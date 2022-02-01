#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"



Image::Image(const char* filename, int channel_force) {
	if(read(filename, channel_force)) {
		printf("Read %s\n", filename);
		size = width*height*channels;
	}
	else {
		printf("Failed to read %s\n", filename);
	}
}

Image::Image(int width, int height, int channels) : width(width), height(height), channels(channels) {
	size = width*height*channels;
	data = new uint8_t[size];
}

Image::Image(const Image& img) : Image(img.width, img.height, img.channels) {
	memcpy(data, img.data, size);
}

Image::~Image() {
	stbi_image_free(data);
}

bool Image::read(const char* filename, int channel_force) {
	data = stbi_load(filename, &width, &height, &channels, channel_force);
	channels = channel_force == 0 ? channels : channel_force;
	return data != NULL;
}

bool Image::write(const char* filename) {
	ImageType type = get_file_type(filename);
	int success;
  switch (type) {
    case PNG:
      success = stbi_write_png(filename, width, height, channels, data, width*channels);
      break;
    case BMP:
      success = stbi_write_bmp(filename, width, height, channels, data);
      break;
    case JPG:
      success = stbi_write_jpg(filename, width, height, channels, data, 100);
      break;
    case TGA:
      success = stbi_write_tga(filename, width, height, channels, data);
      break;
  }
  if(success != 0) {
    printf("\e[32mWrote \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, width, height, channels, size);
    return true;
  }
  else {
    printf("\e[31;1m Failed to write \e[36m%s\e[0m, %d, %d, %d, %zu\n", filename, width, height, channels, size);
    return false;
  }
}

ImageType Image::get_file_type(const char* filename){
  const char* file_ext = strrchr(filename, '.');
  if(file_ext!=nullptr){
    if(strcmp(file_ext, ".png") == 0){
      return PNG;
    }
    else if(strcmp(file_ext, ".jpg") == 0){
      return JPG;
    }
    else if(strcmp(file_ext, ".bmp") == 0){
      return BMP;
    }
    else if(strcmp(file_ext, ".tga") == 0){
      return TGA;
    }
    else{
      return PNG;
    }

  }

}


Image& Image::grayscale_avg(){
  
  if(channels < 3){
    printf("Image %p has less than three channels");
  }

}
Image& Image::grayscale_lumins(){

}





