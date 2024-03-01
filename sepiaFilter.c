 #include <stdio.h>
 #include <stdlib.h>

 #define MAX_VALUE 255

int main(int argc, char* argv[]){

    FILE* input = fopen("images/lena_color.bmp","rb");
    FILE* output = fopen("images/lena_sepia.bmp", "wb");

    unsigned char header[54];
    fread(header, sizeof(unsigned char), 54, input);

    int width = *(int*)&header[18];
    int height = *(int*)&header[22];
    int bitDepth = *(int*)&header[28];

    int size = width * height;
    unsigned char buffer[size][3];
    int i, r, g, b;
    for(i = 0; i < size; i++){
        fread(buffer[i], sizeof(unsigned char), 3, input);
        b = (buffer[i][0]*0.393) + (buffer[i][1]*0.769)	+ (buffer[i][2]*0.189);
		g = (buffer[i][0]*0.349) + (buffer[i][1]*0.686)	+ (buffer[i][2]*0.168);
		r = (buffer[i][0]*0.272) + (buffer[i][1]*0.534)	+ (buffer[i][2]*0.131);
        if(r > MAX_VALUE){											
			r = MAX_VALUE;
		}
		if(g > MAX_VALUE){
			g = MAX_VALUE;
		}
		if(b > MAX_VALUE){
			b = MAX_VALUE;
		}
        buffer[i][0] = r;
        buffer[i][1] = g;
        buffer[i][2] = b;
    }

    fwrite(header, sizeof(unsigned char), 54, output);
    for(i = 0; i < size; i++){
        fwrite(buffer[i], sizeof(unsigned char), 3, output);
    }

    fclose(input);
    fclose(output);

    return 0;

}