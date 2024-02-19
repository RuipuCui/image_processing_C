 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char* argv[]){

    FILE* input = fopen("images/lena_color.bmp","rb");
    FILE* output = fopen("images/lena_copy.bmp", "wb");

    unsigned char header[54];
    unsigned char colourTable[1024];

    int byteread = fread(header, sizeof(unsigned char), sizeof(header), input);
    if(byteread != 54){
        perror("Header readed unsuccessfully");
        fclose(input);
        return 1;
    }

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];

    if(bitDepth <= 8){
        fread(colourTable, sizeof(unsigned char), sizeof(colourTable), input);
    }

    printf("width: %d\n", width);
    printf("height: %d\n", height);

    unsigned char buffer[height * width];

    int pixelbytes = fread(buffer, sizeof(unsigned char), (height * width), input);
    if(pixelbytes != height*width){
        perror("Pixel information readed unsuccessfully");
        fclose(input);
        return 2;
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