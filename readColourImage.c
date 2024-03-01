 #include <stdio.h>
 #include <stdlib.h>

int main(int argc, char* argv[]){

    FILE* input = fopen("images/lena_color.bmp","rb");
    FILE* output = fopen("images/lena_copy.bmp", "wb");

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, input);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];

    int size = width * height;
    unsigned char buffer[size][3];
    int i;
    for(i = 0; i < size; i++){
        fread(buffer[i], sizeof(unsigned char), 3, input);
    }

    fwrite(header, sizeof(unsigned char), 54, output);
    for(i = 0; i < size; i++){
        fwrite(buffer[i], sizeof(unsigned char), 3, output);
    }

    fclose(input);
    fclose(output);

    return 0;

}