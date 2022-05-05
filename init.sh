#!/bin/sh
echo "--------------------------------------------Compilando lab3------------------------------"
make 
echo "------------------------------------------Ejecutando programa----------------------------"
echo "Los nombres de las imagenes se da por hecho que son formato .pgm y estan en el directorio ./img/"
echo -n "Imagen base:"
read imagen_base
echo -n "Recorte de imagen:"
read recorte
for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
do 
  date +"[ %r]"
  echo Ejecucion $i
  perf stat ./bin/main $imagen_base $recorte $i  
done
date +"[ %r]"
echo "Ejecucion lista"

