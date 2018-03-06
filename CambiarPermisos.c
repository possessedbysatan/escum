#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
int main(int argc, char *argv[])
{
    char nombre, buffer[100], permisos; int permisos_int;
if (argv[1]==NULL)
{
    printf("[ERROR] Uso: ./p2 (ruta donde se encuentra el archivo a modificar)\n");
    exit(-1);
}
else
{
DIR* carpeta = opendir(argv[1]); //Se verifica si ya existe el directorio
if (carpeta)    
{
    printf("[  OK ] Directorio encontrado\n"); //Salir si ya existe el directorio
    DIR *d;
    struct dirent *carpeta;
    d = opendir(argv[1]); //Para abrir el directorio en el que se encuentra
    if (d) {
    while ((carpeta = readdir(d)) != NULL) { //lista todo hasta que sea el 'fin' de la carpeta
      if (carpeta->d_type == DT_REG) //omite cualquier cosa que no sea un archivo regular 
        printf("%s\n", carpeta->d_name); //imprime todos los archivos dentro de la carpeta
    }
    closedir(d);
    printf("Ingrese el nombre de cualquier archivo anteriormente mostrado para cambiar permisos: \n");
    scanf("%s",&nombre);
    sprintf(buffer, "%s", &nombre); // convierte el numero a cadena para poder usar strtol (convertir a octal) 
    printf("Ingrese permisos en octal para cambiar: \n");
    scanf("%s",&permisos);
    permisos_int = strtol(&permisos, 0, 8); //convierte de octal a decimal
    printf("[ INFO] Permisos en decimal: %d\n",permisos_int);
    chdir(argv[1]); //cambia al directorio deseado
    if(chmod(buffer,permisos_int)==0) //chmod lee los permisos en decimal, conversion necesaria
        printf("[  OK ] Permisos cambiados correctamente.\n");
    else
        printf("[ERROR] No se han podido cambiar los permisos.\n");
}// gcc -Wall CambiarPermisos.c  -o p2
}
else
    printf("[ERROR] No existe el directorio %s\n", argv[1]); 
} // ./p2 keks
} //stat -c '%a %n' keks/*
