#include <stdio.h>
#include <stdlib.h>

int main ()
{
  FILE* fp = fopen("./img/DSC_2337_baw.bmp","rb");
  // FILE* fp = fopen("./img/test.bmp","rb");   //read the file//
  // FILE* fp = fopen("./img/negro.bmp","rb");   //read the file//

  if(fp==NULL)
  {
    perror("Error abriendo imagen");
    exit(EXIT_FAILURE);
  }

  unsigned char imageHeader[54];

  for(int i=0;i<54;i++)//read the 54 byte header from fIn
  {									
    imageHeader[i] = (unsigned char) getc(fp);								
  }

  int width = *(int*)&imageHeader[18];
  int height = *(int*)&imageHeader[22];
  short int bitDepth = *(short int*)&imageHeader[28];
  int colorused = *(int*)&imageHeader[46];

  printf("w:%d,h:%d,D:%d,cn:%d\n",width,height,bitDepth,colorused);

  if(bitDepth <= 8)	// COLOR TABLE Present
    fseek(fp, 4 * colorused, SEEK_CUR);


  int imgDataSize = width * height;		//calculate image size

  short int temp, matriz_mono[imgDataSize];   		

  short int azul,
        verde,
        rojo;

  for(int i=0; i<imgDataSize;i++)
  {
    azul = (short int)getc(fp);                   //blue
    verde = (short int)getc(fp);                   //green
    rojo = (short int)getc(fp);                   //red

    temp =(short int) ((rojo * 0.3) + (verde * 0.59) + (azul * 0.11)); //conversion formula of rgb to gray

    matriz_mono[i] = temp;
  }
  int i=*matriz_mono;
  i=i;
  // for (int i=1; i<=imgDataSize; i++)
  // {
  //   printf("%d |",(int)matriz_mono[i-1]);
  //   if(i%width==0)
  //     printf("\n");
  // }
  fclose(fp);
  return 0;
}
