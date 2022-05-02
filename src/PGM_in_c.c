// Codigo extraido de : https://www.geeksforgeeks.org/how-to-read-a-pgmb-format-image-in-c/
// C Program to read a PGMB image
// and print its parameters
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing the
// image data
typedef struct PGMImage {
  char tipo_pgm[3];
  unsigned char** matriz;
  uint ancho;
  uint alto;
  unsigned short int valor_max;
} PGMImage;

// Function to ignore any comments
// in file
void ignoreComments(FILE* fp)
{
  int ch;
  char line[100];

  // Ignore any blank lines
  while ((ch = fgetc(fp)) != EOF
      && isspace(ch))
    ;

  // Recursively ignore comments
  // in a PGM image commented lines
  // start with a '#'
  if (ch == '#') {
    fgets(line, sizeof(line), fp);
    ignoreComments(fp);
  }
  else
    fseek(fp, -1, SEEK_CUR);
}

// Function to open the input a PGM
// file and process it
bool openPGM(PGMImage* pgm,
    const char* filename)
{
  // Open the image file in the
  // 'read binary' mode
  FILE* pgmfile = fopen(filename, "rb");

  // If file does not exist,
  // then return
  if (pgmfile == NULL) {
    printf("File does not exist\n");
    return false;
  }

  ignoreComments(pgmfile);
  fscanf(pgmfile, "%s",
      pgm->tipo_pgm);

  // Check for correct PGM Binary
  // file type
  if (strcmp(pgm->tipo_pgm, "P5")) {
    fprintf(stderr, "Wrong file type!\n");
    exit(EXIT_FAILURE);
  }

  ignoreComments(pgmfile);

  // Read the image dimensions
  fscanf(pgmfile, "%d %d",(int*) &(pgm->ancho), (int*)&(pgm->alto));

  // ignoreComments(pgmfile);

  // Read maximum gray value
  fscanf(pgmfile, "%d", (int*)&(pgm->valor_max));
  // ignoreComments(pgmfile);

    // Allocating memory to store
    // img info in defined struct
  pgm->matriz = malloc(pgm->alto * sizeof(unsigned char*));

  // Storing the pixel info in
  // the struct
  if (pgm->tipo_pgm[1] == '5') {

    fgetc(pgmfile);

    for (uint i = 0; i < pgm->alto; i++)
    {
      pgm->matriz[i] = malloc(pgm->ancho * sizeof(unsigned char));

      // If memory allocation
      // is failed
      if (pgm->matriz[i] == NULL)
      {
        fprintf(stderr, "malloc failed\n");
        exit(1);
      }

      // Read the gray values and
      // write on allocated memory
      fread(pgm->matriz[i], sizeof(unsigned char), pgm->ancho, pgmfile);
    }
  }

  // Close the file
  fclose(pgmfile);

  return true;
}

// Function to print the file details
void printImageDetails(PGMImage* pgm,
    const char* filename)
{
  FILE* pgmfile = fopen(filename, "rb");

  // Retrieving the file extension
  char* ext = strrchr(filename, '.');

  if (!ext)
    printf("No extension found"
        "in file %s",
        filename);
  else
    printf("File format"
        " : %s\n",
        ext + 1);

  printf("PGM File type : %s\n",
      pgm->tipo_pgm);

  // Print type of PGM file, in ascii
  // and binary format
  if (!strcmp(pgm->tipo_pgm, "P2"))
    printf("PGM File Format:"
        "ASCII\n");
  else if (!strcmp(pgm->tipo_pgm,
        "P5"))
    printf("PGM File Format:"
        " Binary\n");

  printf("Width of img : %d px\n",
      pgm->ancho);
  printf("Height of img : %d px\n",
      pgm->alto);
  printf("Max Gray value : %d\n",
      pgm->valor_max);

  // close file
  fclose(pgmfile);
}

bool crear_imagen(PGMImage* pgm,
    const char* filename)
{
  // Open the image file in the
  // 'read binary' mode
  FILE* pgmfile = fopen(filename, "wb");

  // If file does not exist,
  // then return
  if (pgmfile == NULL) {
    printf("Error al abrir el archivo\n");
    return false;
  }


  // Check for correct PGM Binary
  // file type
  if (fprintf(pgmfile, "%s\n", pgm->tipo_pgm)<0) {
    fprintf(stderr, "Error escribiendo tipo!\n");
    exit(EXIT_FAILURE);
  }

  // Read the image dimensions
  if(fprintf(pgmfile, "%d %d\n", (int)(pgm->ancho), (int)(pgm->alto))<0)
  {
    fprintf(stderr, "Error escribiendo tamanios!\n");
    exit(EXIT_FAILURE);
  }


  // Read maximum gray value
  if(fprintf(pgmfile, "%d\n", (int)(pgm->valor_max))<0)
  {
    fprintf(stderr, "Error escribiendo valor maximo!\n");
    exit(EXIT_FAILURE);
  }

  // Storing the pixel info in
  // the struct
  unsigned char temp;
  // image = pgm->matriz;
  for (uint i = 0; i < pgm->alto; i++) {
    for (uint j = 0; j < pgm->ancho; j++) {
      temp = (unsigned char)(pgm->matriz[i][j]);

      // Writing the gray values in the 2D array to the file
      fprintf(pgmfile, "%c", temp);
    }
  }

  // Close the file
  fclose(pgmfile);

  return true;
}

