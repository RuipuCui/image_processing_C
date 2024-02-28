#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	FILE *fIn = fopen("images/lena512.bmp","rb");
	FILE *fOut = fopen("images/lena_gray.bmp","wb");

	int i,j,x,y;
	unsigned char header[54];

    fread(header, sizeof(unsigned char), 54, fIn);
	fwrite(header,sizeof(unsigned char),54,fOut);

	int height = *(int*)&header[18];
	int width = *(int*)&header[22];
	int bitDepth = *(int*)&header[28];

    if(bitDepth <= 8){
        unsigned char colourTable[1024];
        fread(colourTable, sizeof(unsigned char), 1024, fIn);
        fwrite(colourTable, sizeof(unsigned char), 1024, fOut);
    }

	printf("width: %d\n",width);
	printf("height: %d\n",height );

	int size = height*width;

	unsigned char buffer[size],out[size];
	
	float v=1.0 / 9.0;											
	float kernel[3][3]={{v,v,v},
						{v,v,v},
						{v,v,v}};
	
	fread(buffer,sizeof(unsigned char),size,fIn);

	for(i=0;i<size;i++)
	{
		out[i] = buffer[i];	
	}

	for(x=1;x<height-1;x++)
	{
		for(y=1;y<width-1;y++)
		{
			float sum= 0.0;
			for(i=-1;i<=1;++i)									
			{
				for(j=-1;j<=1;++j)
				{
					sum=sum+(float)kernel[i+1][j+1]*buffer[(x+i)*width+(y+j)];
				}
			}
			out[(x)*width+(y)]=sum;
		}
	}

	fwrite(out,sizeof(unsigned char),size,fOut);

	fclose(fIn);
	fclose(fOut);
	return 0;
}