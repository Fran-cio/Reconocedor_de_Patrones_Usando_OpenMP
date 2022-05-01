#include "./src/PGM_in_c.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main ()
{
  const char* imagen_base= "./img/pibes.pgm";
  const char* imagen_cortada = "./img/pibes_test.pgm";

  PGMImage* str_imagen_base = malloc(sizeof(PGMImage));
  PGMImage* str_imagen_cortada = malloc(sizeof(PGMImage));

  // Process the image and print
  // its details
  if (openPGM(str_imagen_base, imagen_base))
    printImageDetails(str_imagen_base, imagen_base);

  if (openPGM(str_imagen_cortada, imagen_cortada))
    printImageDetails(str_imagen_cortada, imagen_cortada);

  unsigned char** matx_base,
           **matx_recortada;

  matx_base = str_imagen_base->matriz;
  matx_recortada = str_imagen_cortada->matriz;

  uint const ancho_base = str_imagen_base -> ancho,
       alto_base = str_imagen_base -> alto,
       ancho_cortada = str_imagen_cortada -> ancho,
       alto_cortada = str_imagen_cortada -> alto;

  uint **matx_distancia_uint = malloc(alto_base * sizeof(uint*));

  for(uint i=0;i<alto_base;i++)
  {
    matx_distancia_uint[i] = malloc(ancho_base * sizeof(uint));
    for(uint j=0;j<ancho_base;j++)
      matx_distancia_uint[i][j] = 255;
  }
  uint valor_max = 0;

  for (uint i= 0; i < (alto_base - alto_cortada) ; i++) 
  {
    for (uint j=0; j < (ancho_base - ancho_cortada) ; j++)
    {
      uint temp = 0;
      for (uint k=0; k < alto_cortada ; k++)
      {
        uint x = i + k;
        for (uint l=0; l <  ancho_cortada; l++)
        {
          uint y = j + l;

          int distancia = (matx_base[x][y] - matx_recortada[k][l]); 

          temp += (unsigned) (distancia * distancia);
        }
      }
      if(temp>valor_max) valor_max = temp;

      if(temp==0)
        printf("\nes igual");

      printf("\r%d cargado",i*100/(alto_base - alto_cortada));
      matx_distancia_uint[i + (alto_cortada/2)][j + (ancho_cortada/2)] = temp;
    }
  }
  printf("\n");

  unsigned char **matx_distancia_char = malloc(alto_base * sizeof(unsigned char*));

  for (uint i=0; i < alto_base; i++)
  {
    matx_distancia_char[i] = malloc(ancho_base * sizeof(unsigned char));
    for(uint j=0; j < ancho_base; j++)
      matx_distancia_char[i][j] = 0;
  }

  for (uint i=alto_cortada/2; i < (alto_base-alto_cortada/2) ; i++)
    for(uint j=ancho_cortada/2; j < (ancho_base-ancho_cortada/2); j++)
      matx_distancia_char[i][j] =(unsigned char) ((double)(matx_distancia_uint[i][j])*255/valor_max);

  PGMImage* str_imagen_dist = malloc(sizeof(PGMImage));
  str_imagen_dist->ancho = ancho_base;
  str_imagen_dist->alto = alto_base;
  strcpy(str_imagen_dist->tipo_pgm, "P5");
  str_imagen_dist->valor_max = 255;
  str_imagen_dist->matriz = matx_distancia_char;

  crear_imagen(str_imagen_dist, "./img/mapa_distancia.pgm");

  for(uint i=0;i<str_imagen_dist->alto;i++)
  {
    for(uint j=0;j<str_imagen_dist->ancho;j++)
    {
      printf("|%d",str_imagen_dist ->matriz[i][j]);
    }
    printf("|\n");
  }


  free(str_imagen_cortada);
  free(str_imagen_dist);
  free(str_imagen_base);
  free(matx_distancia_uint);
  free(matx_distancia_char);

  return 0;
}

