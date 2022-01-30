#include "image.h"

int main(int argc, char* argv[]){
    Image test("test.jpg");
    test.write("new.png");
    Image copy = test;
    for(int i = 0; i<copy.width*copy.channels; ++i){
        copy.data[i] = 255;
    }




    return 0;
}