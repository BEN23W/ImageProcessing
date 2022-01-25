

struct Image{
    uint8_t* data = NULL; //unsigned int 8 bytes
    size_t size = 0; //
    int width;
    int height;
    int channels;

    Image(const char* filename);
    Image(int width, int height, int channels);
    Image(cont Image& img);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename);
}