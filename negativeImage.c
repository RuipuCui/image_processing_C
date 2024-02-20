#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    FILE* input = fopen("images/lena512.bmp", "rb");
    FILE* output = fopen("images/lena_negative.bmp", "wb");

    unsigned char* imageData;
    unsigned char* newimageData;
    unsigned char imageHeader[54];
    unsigned char colorTable[1024];

    fread(imageHeader, sizeof(unsigned char), 54, input);

    int width = *(int*)&imageHeader[18];
    int height = *(int*)&imageHeader[22];
    int bitDepth = *(int*)&imageHeader[28];

    int imageDataSize = width * height;

    imageData = (unsigned char*)malloc(imageDataSize * sizeof(unsigned char));
    newimageData = (unsigned char*)malloc(imageDataSize * sizeof(unsigned char));

    if(bitDepth <= 8){
        fread(colorTable, sizeof(unsigned char), 1024, input);
    }

    fread(imageData, sizeof(unsigned char), imageDataSize, input);

    int row, colume;
    for(row = 0; row < height; row++){
        for(colume = 0; colume < width; colume++){
            newimageData[row*width + colume] = 255 - imageData[row*width + colume];
        }
    }

    fwrite(imageHeader, sizeof(unsigned char), 54, output);
    if(bitDepth <= 8){
        fwrite(colorTable, sizeof(unsigned char), 1024, output);
    }
    fwrite(newimageData, sizeof(unsigned char), imageDataSize, output);
    fclose(input);
    fclose(output);
}