#!/bin/sh
echo "--------------------------------------------Compilando lab3------------------------------"
make 
echo "------------------------------------------Ejecutando programa----------------------------"
echo "Los nombres de las imagenes se da por hecho que son formato .pgm y estan en el directorio ./img/"
echo -n "Imagen base:"
read imagen_base
echo -n "Recorte de imagen:"
read recorte
echo -n "Numero de cores:"
read cores
perf stat ./bin/main $imagen_base $recorte $cores  
echo "Ejecucion lista"

