// Codigo extraido de : https://www.geeksforgeeks.org/how-to-read-a-pgmb-format-image-in-c/
// C Program to read a PGMB image
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// image data
typedef struct PGMImage 
{
  char tipo_pgm[3];
  unsigned char** matriz;
  uint ancho;
  uint alto;
  unsigned short int valor_max;
} PGMImage;

void ignorarcomentarios(FILE* fp)
{
  int ch;
  char line[100];

  while ((ch = fgetc(fp)) != EOF && isspace(ch));

  if (ch == '#') 
  {
    fgets(line, sizeof(line), fp);
    ignorarcomentarios(fp);
  }
  else
    fseek(fp, -1, SEEK_CUR);
}

void abrir_imagen_PGM(PGMImage* pgm, const char* path)
{
  FILE* archivo_pgm = fopen(path, "rb");

  if (archivo_pgm == NULL) {
    printf("Archivo no encontrado\n");
    exit(EXIT_FAILURE);
  }

  ignorarcomentarios(archivo_pgm);
  fscanf(archivo_pgm, "%s", pgm->tipo_pgm);

  if (strcmp(pgm->tipo_pgm, "P5")) 
  {
    fprintf(stderr, "Formato de archivo erroneo!\n");
    exit(EXIT_FAILURE);
  }

  ignorarcomentarios(archivo_pgm);

  fscanf(archivo_pgm, "%d %d",(int*) &(pgm->ancho), (int*)&(pgm->alto));

  fscanf(archivo_pgm, "%d", (int*)&(pgm->valor_max));
  pgm->matriz = malloc(pgm->alto * sizeof(unsigned char*));

  if (pgm->tipo_pgm[1] == '5') 
  {
    fgetc(archivo_pgm);

    for (uint i = 0; i < pgm->alto; i++)
    {
      pgm->matriz[i] = malloc(pgm->ancho * sizeof(unsigned char));

      if (pgm->matriz[i] == NULL)
      {
        fprintf(stderr, "error en el malloc\n");
        exit(1);
      }

      fread(pgm->matriz[i], sizeof(unsigned char), pgm->ancho, archivo_pgm);
    }
  }

  fclose(archivo_pgm);
}

void imprimir_detalles_de_imagen(PGMImage* pgm, const char* ruta)
{
  FILE* archivo_pgm = fopen(ruta, "rb");

  char* extension = strrchr(ruta, '.');

  if (!extension)
    printf("No se encontro la extension del archivo %s", ruta);
  else
    printf("Formato de archivo: %s\n", extension + 1);

  printf("Tipo de PGM: %s\n", pgm->tipo_pgm);

  if (!strcmp(pgm->tipo_pgm, "P2"))
    printf("Formato PGM: ASCII\n");
  else if (!strcmp(pgm->tipo_pgm, "P5"))
    printf("Foramto PGM: Binary\n");

  printf("Ancho de img : %d px\n", pgm->ancho);
  printf("Alto de img : %d px\n", pgm->alto);
  printf("Valor maximo de gris: %d\n", pgm->valor_max);

  fclose(archivo_pgm);
}

bool crear_imagen(PGMImage* pgm, const char* ruta)
{
  FILE* archivo_pgm = fopen(ruta, "wb");

  if (archivo_pgm == NULL) {
    printf("Error al abrir el archivo\n");
    exit(EXIT_FAILURE);
  }

  if (fprintf(archivo_pgm, "%s\n", pgm->tipo_pgm)<0) {
    fprintf(stderr, "Error escribiendo tipo!\n");
    exit(EXIT_FAILURE);
  }

  if(fprintf(archivo_pgm, "%d %d\n", (int)(pgm->ancho), (int)(pgm->alto))<0)
  {
    fprintf(stderr, "Error escribiendo tamanios!\n");
    exit(EXIT_FAILURE);
  }

  if(fprintf(archivo_pgm, "%d\n", (int)(pgm->valor_max))<0)
  {
    fprintf(stderr, "Error escribiendo valor maximo!\n");
    exit(EXIT_FAILURE);
  }

  unsigned char temp;
  unsigned char** imagen = pgm->matriz;
  for (uint i = 0; i < pgm->alto; i++) {
    for (uint j = 0; j < pgm->ancho; j++) {
      temp = (unsigned char)(imagen[i][j]);

      fprintf(archivo_pgm, "%c", temp);
    }
  }

  fclose(archivo_pgm);

  return true;
}

