#include <sys/types.h>
#include "./PGM_in_c.h"

void dibujar_cuadrado(uint x, uint y, uint alto, uint ancho, 
    unsigned char **matrix);

PGMImage* generar_estructura(uint ancho, uint alto, char* tipo, 
    short unsigned int valor_max, unsigned char **matrix);

unsigned char** computar(PGMImage* str_imagen_base, PGMImage* str_imagen_cortada,
    uint *x_min, uint *y_min);


