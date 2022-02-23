#include "image.h"

int main(int argc, char* argv[]){
    Image test("test.jpg");
    /*test.write("new.png");
    Image copy = test;

    for(int i = 0; i<copy.width*copy.channels; ++i){
        copy.data[i] = 255;
    }

    copy.write("copy.png");
    Image blank(100,100,3);
    blank.write("blank.jpg"); */

   /* Image gray_avg = test;
    Image gray_lum = test;
    gray_avg.grayscale_avg();
    gray_avg.write("gray_avg.png");
    gray_lum.grayscale_lumins();
    gray_lum.write("gray_lum.png");*/
    Image color_mask = test;
    color_mask.colorMask(0,1,1);
    color_mask.write("new_mask.png");


    return 0;
}