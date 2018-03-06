#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
        struct stat archivillo;
if (argv[1]==NULL)
{
    printf("[ERROR] Uso: ./p3 (ruta donde se encuentran los archivos a revisar\n");
    exit(-1);
}
else
{
DIR* dir = opendir(argv[1]); //Se verifica si ya existe el directorio
if (dir)    
{
    printf("[  OK ] Directorio %s encontrado\n", argv[1]); //Salir si ya existe el directorio
    chdir(argv[1]);
    DIR *d;
    struct dirent *dir;
    d = opendir("."); //Para abrir el directorio en el que se encuentra
    if (d) {
    while ((dir = readdir(d)) != NULL) { //lista todo hasta que sea el 'fin' de la carpeta
      if (dir->d_type == DT_REG) {//omite cualquier cosa que no sea un archivo regular 
        printf("%s ", dir->d_name); //imprime todos los archivos dentro de la carpeta
        if(stat(dir->d_name, &archivillo)==0) //abrir cada archivo que se encuentre para mostrar sus atributos
        printf(" - - - Tam(Bytes): %ld, Fecha: %s", archivillo.st_size, ctime(&archivillo.st_atim.tv_sec)); //convertir la fecha a formato legible
        else
            printf("[ERROR] No se pudo leer un archivo.\n");
    }
    }
    closedir(d);
}// gcc -Wall ListadorDeArchivos.c -o p3
}
else
    printf("[ERROR] No existe o no se pudo acceder a %s\n", argv[1]); 
} // ./p2 keks
} //stat -c '%a %n' keks/*
