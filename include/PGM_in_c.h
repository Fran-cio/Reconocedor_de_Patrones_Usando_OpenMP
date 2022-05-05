// image data
#include <stdio.h>
#include <sys/types.h>

typedef struct PGMImage 
{
  char tipo_pgm[3];
  unsigned char** matriz;
  uint ancho;
  uint alto;
  unsigned short int valor_max;
} PGMImage;

void ignorarcomentarios(FILE* fp);
void abrir_imagen_PGM(PGMImage* pgm, const char* path);
void imprimir_detalles_de_imagen(PGMImage* pgm, const char* ruta);
void crear_imagen(PGMImage* pgm, const char* ruta);



