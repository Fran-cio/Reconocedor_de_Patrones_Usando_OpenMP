#include "./include/recursos.h"

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *generar_ruta(char* palabra);

int main (int argc, char *argv[])
{
  if (argc < 4)
  {
    printf("Falto el nombre de las imagenes");
    exit(EXIT_FAILURE);
  }

  if(atoi(argv[3])==0)
  {
    printf("Se asigno numero generico de hilos\n");
  }

  uint x_min,
       y_min;

  omp_set_num_threads(atoi(argv[3]));
  omp_set_dynamic(1);

  char* imagen_base = generar_ruta(argv[1]);

  char* imagen_cortada = generar_ruta(argv[2]);

  PGMImage* str_imagen_base = malloc(sizeof(PGMImage));
  PGMImage* str_imagen_cortada = malloc(sizeof(PGMImage));

  abrir_imagen_PGM(str_imagen_base, imagen_base);
  // imprimir_detalles_de_imagen(str_imagen_base, imagen_base);
  abrir_imagen_PGM(str_imagen_cortada, imagen_cortada);
  // imprimir_detalles_de_imagen(str_imagen_cortada, imagen_cortada);

  unsigned char **matx_distancia_char = 
    computar(str_imagen_base, str_imagen_cortada, &x_min, &y_min);

  PGMImage* str_imagen_dist = generar_estructura(str_imagen_base->ancho,
      str_imagen_base->alto, "P5", 255, matx_distancia_char);
  crear_imagen(str_imagen_dist, "./img/imagenes_generadas/mapa_distancia.pgm");

  dibujar_cuadrado(x_min, y_min, str_imagen_cortada->alto, 
      str_imagen_cortada->ancho, str_imagen_base ->matriz); 
  PGMImage* str_imagen_marcada = generar_estructura(str_imagen_base->ancho, 
      str_imagen_base->alto, "P5", 255, str_imagen_base ->matriz);
  crear_imagen(str_imagen_marcada , "./img/imagenes_generadas/foto_marcada.pgm");

  free(str_imagen_cortada);
  free(str_imagen_dist);
  free(str_imagen_base);
  free(str_imagen_marcada);
  free(matx_distancia_char);
  free(imagen_cortada);
  free(imagen_base);

  return 0;
}

char *generar_ruta(char* palabra)
{
  char *ruta  = "./img/";
  char *path = malloc(32);
  path = strcpy(path,ruta);
  path = strcat(path,palabra);
  path = strcat(path, ".pgm");

  return path;
}
