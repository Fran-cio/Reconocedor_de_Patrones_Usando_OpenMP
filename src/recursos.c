#include "./PGM_in_c.c"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


PGMImage* generar_estructura(uint ancho, uint alto, char* tipo, 
    short unsigned int valor_max, unsigned char **matrix)
{
  PGMImage* str_imagen = malloc(sizeof(PGMImage));
  str_imagen->ancho = ancho;
  str_imagen->alto = alto;
  strcpy(str_imagen->tipo_pgm, tipo);
  str_imagen->valor_max = valor_max;
  str_imagen->matriz = matrix;

  return str_imagen;
}

void dibujar_cuadrado(uint x, uint y, uint alto, uint ancho, unsigned char **matrix)
{
#pragma omp parallel 
  {
#pragma omp for 
    for (uint i=x; i < (x + alto) ; i++)
    {
      matrix[i][y] = 0;
      matrix[i][y + 1] = 0;
      matrix[i][y + ancho] = 0;
      matrix[i][y - 1 + ancho] = 0;
    }

#pragma omp for
    for(uint j=y; j < (y + ancho); j++)
    {
      matrix[x][j] = 0;
      matrix[x + 1][j] = 0;
      matrix[x - 2 + alto][j] = 0;
      matrix[x - 1 + alto][j] = 0;
    }
  }
}

unsigned char** generar_y_llenar_matriz(uint alto, uint ancho,
    unsigned char relleno)
{
  unsigned char **matriz_generada = malloc(alto * sizeof(unsigned char*));

  uint i,j;
#pragma omp parallel 
  {
#pragma omp for private(i,j) 
    for(i=0;i<alto;i++)
    {
      matriz_generada[i] = malloc(ancho * sizeof(unsigned char));
      for(j=0;j<ancho;j++)
        matriz_generada[i][j] = relleno;
    }
  }

  return matriz_generada;
}

unsigned char** computar(PGMImage* str_imagen_base, PGMImage* str_imagen_cortada,
    uint *x_min, uint *y_min)
{
  unsigned char** matx_base = str_imagen_base->matriz,
           **matx_recortada = str_imagen_cortada->matriz;;

  uint ancho_base = str_imagen_base -> ancho,
       alto_base = str_imagen_base -> alto,
       ancho_cortada = str_imagen_cortada -> ancho,
       alto_cortada = str_imagen_cortada -> alto;

  uint valor_max = 255 * alto_cortada * ancho_cortada
    ,valor_min = 1; 

  unsigned char **matx_distancia_char = generar_y_llenar_matriz(alto_base,
      ancho_base, 0); 

#pragma omp parallel 
  {
#pragma omp for
    for(uint i=0;i<alto_base;i++)
    {
      matx_distancia_char[i] = malloc(ancho_base * sizeof(unsigned char));
      memset(matx_distancia_char[i], 0, ancho_base * sizeof(unsigned char));
    }
  }

  uint i,j,k,l,temp = 0;
#pragma omp parallel
  {
#pragma omp for collapse(2) reduction(+:temp) private(i, j, k, l) schedule(dynamic)
    for (i = 0; i <= (alto_base - alto_cortada ) ; i++) 
    {
      for (j = 0; j <= (ancho_base - ancho_cortada ) ; j++)
      {
        temp = 0;
        for (k = 0; k < alto_cortada ; k++)
        {
          uint x = i + k;
          for (l = 0; l <  ancho_cortada; l++)
          {
            uint y = j + l;

            int distancia = (matx_base[x][y] - matx_recortada[k][l]); 

            temp += (unsigned) (distancia * distancia);
          }
        }

        if(temp == 0)
        {
          valor_min = 0;
          *x_min=i;
          *y_min=j;
        }

        // printf("\r ---- %.2f%c ----",((float)i*100/(float)(alto_base - alto_cortada)),'%');
        matx_distancia_char[i + (alto_cortada/2)][j + (ancho_cortada/2)] = 
          (unsigned char)(temp/valor_max);
      }
    }
  }
  printf("\n");

  if(valor_min != 0)
  {
    fprintf(stderr, "No se encontro patron\n");
    exit(EXIT_SUCCESS);
  }

  return matx_distancia_char;
}
