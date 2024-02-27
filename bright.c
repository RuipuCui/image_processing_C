#include <stdio.h>
#include <stdlib.h>

#define MAX_COLOR 255
#define BRIGHTNESS_FACTOR 25

int main(int argc, char* argv[]){

    FILE* input = fopen("images/lena512.bmp", "rb");
    FILE* output = fopen("images/lena_bright.bmp", "wb");

    unsigned char header[54];
    unsigned char colourTable[1024];

    fread(header, sizeof(unsigned char), 54, input);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];

    int imageSize = height * width;

    if(bitDepth <=  8){
        fread(colourTable, sizeof(unsigned char), sizeof(colourTable), input);
    }

    unsigned char buffer[imageSize];
    fread(buffer, sizeof(unsigned char), imageSize, input);

    int i;
    int temp;
    for(i = 0; i < imageSize; i++){
        buffer[i] = buffer[i] + BRIGHTNESS_FACTOR;
        if(buffer[i] > MAX_COLOR){
            buffer[i] = MAX_COLOR;
        }
    }

    fwrite(header, sizeof(unsigned char), sizeof(header), output);
    if(bitDepth <= 8){
        fwrite(colourTable, sizeof(unsigned char), sizeof(colourTable), output);
    }
    fwrite(buffer, sizeof(unsigned char), sizeof(buffer), output);

    fclose(input);
    fclose(output);

    return 0;

}