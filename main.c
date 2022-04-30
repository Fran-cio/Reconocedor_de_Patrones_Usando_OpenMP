#include "./src/PGM_in_c.c"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
  const char* imagen_base= "./img/DSC_2337_baw.pgm";
  const char* imagen_cortada = "./img/test.pgm";

  PGMImage* str_imagen_base = malloc(sizeof(PGMImage));
  PGMImage* str_imagen_cortada = malloc(sizeof(PGMImage));



  // Process the image and print
  // its details
  if (openPGM(str_imagen_base, imagen_base))
    printImageDetails(str_imagen_base, imagen_base);

  if (openPGM(str_imagen_cortada, imagen_cortada))
    printImageDetails(str_imagen_cortada, imagen_cortada);

  int maxsize = str_imagen_cortada -> width * str_imagen_cortada ->height;
  for(int i=1;i<=maxsize;i++)
  {
    printf("%d|",str_imagen_cortada ->data[i-1]);
    if(i%str_imagen_cortada ->width ==0)
      printf("\n");
  }

  int maxsiz = str_imagen_base ->width * str_imagen_base ->height;
  for(int i=1;i<=maxsiz;i++)
  {
    printf("%d|",str_imagen_base ->data[i-1]);
    if(i%str_imagen_base ->width ==0)
      printf("\n");
  }

  return 0;
}
