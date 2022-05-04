#include "./src/PGM_in_c.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


uint ancho_base,
     alto_base,
     ancho_cortada,
     alto_cortada;

uint x_min,
     y_min;

void dibujar_cuadrado(uint x, uint y, uint alto, uint ancho, 
    unsigned char **matrix);

PGMImage* generar_estructura(uint ancho, uint alto, char* tipo, 
    short unsigned int valor_max, unsigned char **matrix);

unsigned char** computar(PGMImage* str_imagen_base, PGMImage* str_imagen_cortada);

int main (int argc, char *argv[])
{
  if (argc < 3)
  {
    printf("Falto el nombre de las imagenes");
    exit(EXIT_FAILURE);
  }

  char* ruta  = "./img/";
  char* imagen_base = malloc(32);
  imagen_base = strcpy(imagen_base,ruta);
  imagen_base = strcat(imagen_base, argv[1]);
  imagen_base = strcat(imagen_base, ".pgm");


  char* imagen_cortada = malloc(32);
  imagen_cortada = strcpy(imagen_cortada, ruta);
  imagen_cortada = strcat(imagen_cortada, argv[2]);
  imagen_cortada = strcat(imagen_cortada, ".pgm");

  PGMImage* str_imagen_base = malloc(sizeof(PGMImage));
  PGMImage* str_imagen_cortada = malloc(sizeof(PGMImage));

  abrir_imagen_PGM(str_imagen_base, imagen_base);
  imprimir_detalles_de_imagen(str_imagen_base, imagen_base);

  abrir_imagen_PGM(str_imagen_cortada, imagen_cortada);
  imprimir_detalles_de_imagen(str_imagen_cortada, imagen_cortada);

  free(imagen_cortada);
  free(imagen_base);

  unsigned char **matx_distancia_char = 
    computar(str_imagen_base, str_imagen_cortada);

  PGMImage* str_imagen_dist = generar_estructura(ancho_base, alto_base, "P5",
      255, matx_distancia_char);
  crear_imagen(str_imagen_dist, "./img/imagenes_generadas/mapa_distancia.pgm");

  dibujar_cuadrado(x_min, y_min, alto_cortada, ancho_cortada, 
      str_imagen_base ->matriz); 
  PGMImage* str_imagen_marcada = generar_estructura(ancho_base, alto_base, "P5",
      255, str_imagen_base ->matriz);
  crear_imagen(str_imagen_marcada , "./img/imagenes_generadas/foto_marcada.pgm");

  free(str_imagen_cortada);
  free(str_imagen_dist);
  free(str_imagen_base);
  free(str_imagen_marcada);
  free(matx_distancia_char);

  return 0;
}

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
  for (uint i=x; i < (x + alto) ; i++)
  {
    matrix[i][y] = 0;
    matrix[i][y + 1] = 0;
    matrix[i][y + ancho] = 0;
    matrix[i][y - 1 + ancho] = 0;
  }

  for(uint j=y; j < (y + ancho); j++)
  {
    matrix[x][j] = 0;
    matrix[x + 1][j] = 0;
    matrix[x - 2 + alto][j] = 0;
    matrix[x - 1 + alto][j] = 0;
  }
}

unsigned char** generar_y_llenar_matriz(uint alto, uint ancho,
    unsigned char relleno)
{
  unsigned char **matriz_generada = malloc(alto * sizeof(unsigned char*));

  for(uint i=0;i<alto;i++)
  {
    matriz_generada[i] = malloc(ancho * sizeof(unsigned char));
    for(uint j=0;j<ancho;j++)
      matriz_generada[i][j] = relleno;
  }

  return matriz_generada;
}

unsigned char** computar(PGMImage* str_imagen_base, PGMImage* str_imagen_cortada)
{
  unsigned char** matx_base = str_imagen_base->matriz,
           **matx_recortada = str_imagen_cortada->matriz;;

  ancho_base = str_imagen_base -> ancho;
  alto_base = str_imagen_base -> alto;
  ancho_cortada = str_imagen_cortada -> ancho;
  alto_cortada = str_imagen_cortada -> alto;

  uint valor_max = 255 * alto_cortada * ancho_cortada
    ,valor_min = 1; 

  unsigned char **matx_distancia_char = generar_y_llenar_matriz(alto_base,
      ancho_base, 0); 

  for(uint i=0;i<alto_base;i++)
  {
    matx_distancia_char[i] = malloc(ancho_base * sizeof(unsigned char));
    for(uint j=0;j<ancho_base;j++)
      matx_distancia_char[i][j] = 0;
  }

  for (uint i= 0; i <= (alto_base - alto_cortada ) ; i++) 
  {
    for (uint j=0; j <= (ancho_base - ancho_cortada ) ; j++)
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

      if(temp == 0)
      {
        valor_min = 0;
        x_min=i;
        y_min=j;
      }
      printf("\r ---- %.2f%c ----",((float)i*100/(float)(alto_base - alto_cortada)),'%');
      matx_distancia_char[i + (alto_cortada/2)][j + (ancho_cortada/2)] = 
        (unsigned char)(temp/valor_max);
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
