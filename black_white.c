#include <stdio.h>
#include <stdlib.h>

#define THRESHOLD 128
#define WHITE 255
#define BLACK 0

int main(int argc, char* argv[]){

    FILE* input = fopen("images/lena512.bmp", "rb");
    FILE* output = fopen("images/lena_black_white.bmp", "wb");

    if(input == NULL){
        printf("File does not exit.\n");
    }

    unsigned char header[54];
    unsigned char colourTable[1024];

    fread(header, sizeof(unsigned char), 54, input);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];

    if(bitDepth <= 8){
        fread(colourTable, sizeof(unsigned char), 1024, input);
    }

    int imageSize = width * height;
    unsigned char buffer[imageSize];
    fread(buffer, sizeof(unsigned char), imageSize, input);

    int i;
    for(i = 0; i < imageSize; i++){
        if(buffer[i] > THRESHOLD){
            buffer[i] = WHITE;
        }else{
            buffer[i] = BLACK;
        }
    }
    
    fwrite(header, sizeof(unsigned char), 54, output);
    if(bitDepth <= 8){
        fwrite(colourTable, sizeof(unsigned char), 1024, output);
    }
    fwrite(buffer, sizeof(unsigned char), imageSize, output);

    fclose(input);
    fclose(output);

    return 0;

}