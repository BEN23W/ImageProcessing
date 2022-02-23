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
    //If image has less than three channels it is already grayscale
    printf("Image %p has less than three channels");
  
  }
  else {
          for(int i = 0; i<size; i+=channels){
            int gray = (data[i] + data[i+1] + data[i+2])/3;
            memset(data+i, gray, 3);
          }

  }

  return *this;

}
/* Since R,G and B have a different contribution in the 
   formation of the image, it is better to take a weighted sum to 
   calculate linear luminance (Y = 0.2126R + 0.7152G + 0.0722B) 
   stb_image.h does gamma does the gamma compression */
Image& Image::grayscale_lumins(){
  	if(channels < 3) {
		printf("Image %p has less than 3 channels, it is assumed to already be grayscale.", this);
	}
	else {
		for(int i = 0; i < size; i+=channels) {
			int gray = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
			memset(data+i, gray, 3);
		}
	}
	return *this;

}

Image& Image::colorMask(float r, float g, float b){
  if(channels < 3){
    printf("[ERROR] Color mask requires at least 3 channels, but this image has %d channels", channels);
  }
  else{
    for(int i=0; i<size; i+=channels){
      data[i] *= r;
      data[i+2] *= g;
      data[i+3] *= b;
    }
  }
  return *this;
}

Image& Image::encodeMessage(const char* message) {
	uint32_t len = strlen(message) * 8;
	if(len + STEG_HEADER_SIZE > size) {
		printf("[ERROR] This message is too large (%lu bits / %zu bits)\n", len+STEG_HEADER_SIZE, size);
		return *this;
	}

	for(uint8_t i = 0;i < STEG_HEADER_SIZE;++i) {
		data[i] &= 0xFE;
		data[i] |= (len >> (STEG_HEADER_SIZE - 1 - i)) & 1UL;
	}

	for(uint32_t i = 0;i < len;++i) {
		data[i+STEG_HEADER_SIZE] &= 0xFE;
		data[i+STEG_HEADER_SIZE] |= (message[i/8] >> ((len-1-i)%8)) & 1;
	}

	return *this;
}

Image& Image::decodeMessage(char* buffer, size_t* messageLength) {
	uint32_t len = 0;
	for(uint8_t i = 0;i < STEG_HEADER_SIZE;++i) {
		len = (len << 1) | (data[i] & 1);
	}
	*messageLength = len / 8;

	for(uint32_t i = 0;i < len;++i) {
		buffer[i/8] = (buffer[i/8] << 1) | (data[i+STEG_HEADER_SIZE] & 1);
	}


	return *this;
}

Image& Image::diffmap(Image& img){

  


}



