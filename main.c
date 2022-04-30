#include "./src/PGM_in_c.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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

  uint maxsize = str_imagen_cortada -> ancho * str_imagen_cortada ->alto;
  // uint maxsiz = str_imagen_base ->ancho * str_imagen_base ->alto;

  unsigned char* matx_base,
           *matx_recortada;

  matx_base = str_imagen_base->matriz;
  matx_recortada = str_imagen_cortada->matriz;

  uint const ancho_base = str_imagen_base -> ancho,
       alto_base = str_imagen_base -> alto,
       ancho_cortada = str_imagen_cortada -> ancho,
       alto_cortada = str_imagen_cortada -> alto;

  unsigned char *matx_distancia = malloc(maxsize * sizeof(unsigned char));
  memset(matx_distancia, 0, maxsize);

  const uint ponderado = 1;

  for (uint i= 0; i < (ancho_base - ancho_cortada) ; i++) 
    for (uint j=0; j < (alto_base - alto_cortada) ; j++)
    {
      uint coord_dist = (i + (ancho_cortada>>1)) + (j + (alto_cortada>>1)) ;
      uint temp = 0;
      for (uint k=0; k < ancho_cortada ; k++)
        for (uint l=0; l < alto_cortada ; l++)
        {
          uint x = i + k;
          uint y = j + l;

          uint distancia = (matx_base[x + y] - matx_recortada [k + j]); 

          temp += (unsigned) (distancia * distancia);
        }

      printf("\r%d cargado",i*100/(ancho_base - ancho_cortada));
      matx_distancia[coord_dist] = (unsigned char) ((double)((double)temp/ponderado));
    }

  printf("\n");

  PGMImage* str_imagen_dist = malloc(sizeof(PGMImage));
  str_imagen_dist->ancho = ancho_base;
  str_imagen_dist->alto = alto_base;
  strcpy(str_imagen_dist->tipo_pgm, "P5");
  str_imagen_dist->valor_max = 255;
  str_imagen_dist->matriz = matx_distancia;

  crear_imagen(str_imagen_dist, "./img/mapa_distancia.pgm");

  for(uint i=1;i<=maxsize;i++)
  {
    printf("%d|",str_imagen_dist ->matriz[i-1]);
    if(i%str_imagen_dist->ancho ==0)
      printf("\n");
  }
  return 0;
}

