#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define S_MAX 20
int main(int argc, char *argv[])
{
const char *arreglo_nice[] = {"a1\n", "bb2\n", "ccc3\n", "dddd4\n", "5eeeee\n", "6ffffff\n", "7ggggggg\n"};
if (argv[1]==NULL)
{
	printf("[ERROR] Sin argumentos\n");
	exit(-1);
}
else
{
DIR* dir = opendir(argv[1]); //Se verifica si ya existe el directorio
if (dir)	
{
    printf("[ERROR] Directorio existente\n"); //Salir si ya existe el directorio
    closedir(dir);
    exit(-1);
}
else
{
    printf("[  OK ] creando nuevo directorio \n"); 
    if(mkdir(argv[1], 0755)==0) //Crea el directorio con el path del primer argumento con permisos 0755
    {
    	printf("[  OK ] directorio %s creado exitosamente\n",argv[1]);
    	chdir(argv[1]);			//Entra al directorio creado
    	printf("[ INFO] cantidad maxima de archivos aleatorios: %d\n",S_MAX);
		srand(time(NULL)); // hace aleatorios los numeros
		int alea[S_MAX], s, randIndexArregloNice, i, tamArregloNice; char nombre[15], buffer[5]; 
		tamArregloNice = sizeof(arreglo_nice) / (2*sizeof(int)); // Obtiene la cantidad de cadenas presentes en arreglo_nice
		for(i=0;i<S_MAX;i++)
		{
		nombre[0] = '\0'; //Inicializa una cadena para contener el nombre
		strcat(nombre,"archivo");  //Pega la palabra "archivo" a el nombre
    	alea[i] = rand()%S_MAX; //Obtiene un valor aleatorio entre 0 y S_MAX
	    sprintf(buffer, "%d", alea[i]); // convierte el numero a cadena para utilizar 
	    strcat(nombre,buffer);  //Pega el numero aleatorio al final del archivo
    	creat(nombre,0755); //crea nuevos archivos, vacios, con permisos 0755
    	randIndexArregloNice=rand()%tamArregloNice; //Obtiene un elemento aleatoriamente del arreglo_nice
		s=open(nombre, O_WRONLY | O_APPEND);  //Descriptor del archivo a escribir
		if(write(s, arreglo_nice[randIndexArregloNice], strlen(arreglo_nice[randIndexArregloNice]))==-1)  //Escribe el elemento aleatorio del arreglo a un archivo 
			printf("[ERROR] Imposible escribir a los archivos creados.\n");
		close(s); //Cierra el descriptor del archivo
    }
    }
    else {
    	printf("[ERROR] Algo sucedio mal al crear el directorio.\n ");
    	exit(-1);
    }
}
} // gcc -Wall LinuxSerieAleatoria.c -o p1
} // rm -r keks; ./p1 /home/$USER/Desktop/SO/keks; cat keks/*
