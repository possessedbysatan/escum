#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <dirent.h> 
#include <unistd.h> 
#include <termios.h> 
#include <fcntl.h>
#define BUFFER_SZ 1024
int main(int argc, char * argv[]) {
  char archivillos[512], visualizado[512], fullarchivillos[512], contenido, *string, *nombre_archivo; int i, visor, fuente, destino, bits; void *buf = (char * ) calloc(BUFFER_SZ, 1);
  archivillos[0] = '\0', fullarchivillos[0] = '\0';
  if (argv[1] == NULL || argv[2] == NULL) {
    printf("[ERROR] Uso: ./p4 (ruta absoluta de archivo a visualizar) (ruta absuolta destino de archivos a copiar)\n");
    exit(-1);
  } else {
    DIR* carpeta = opendir(argv[1]); //Se verifica si ya existe el directorio
    DIR* carpetadestino = opendir(argv[2]);
    if (carpeta && carpetadestino) {
      printf("[  OK ] Directorio encontrado\n"); //Salir si ya existe el directorio
      DIR* d;
      struct dirent *carpeta;
      d = opendir(argv[1]); //Para abrir el directorio en el que se encuentra
      if (d) {
        while ((carpeta = readdir(d)) != NULL) { //lista todo hasta que sea el 'fin' de la carpeta
          if (carpeta -> d_type == DT_REG) { //omite cualquier cosa que no sea un archivo regular
            printf("%s\n", carpeta -> d_name); //imprime todos los archivos dentro de la carpeta
            strcat(fullarchivillos, carpeta -> d_name); //pega a fularchivillos el nombre de la carpeta
            strcat(fullarchivillos, ","); //y le pone una coma
          }
        }
        i = strlen(fullarchivillos); //Para obtener la longitud de toda la cadena
        fullarchivillos[i-1] = '\0'; //Quitar la ultima coma
        closedir(d); //cierra el descriptor de la carpeta
        chdir(argv[1]); //cambia al directorio de la primera carpeta
        printf("\nIngrese el archivo del cual desea visualizar su contenido:\n");
        scanf("%s", & visualizado);
        if ((visor = open(visualizado, O_RDONLY))>=0) //abre el archivo como solo lectura
        {
          printf("=========================%s========================\n", visualizado);
          while (read(visor, & contenido, 1) == 1) //descriptor, buffer a almacenar el contenido y cantidad de bytes a leer
            putchar(contenido); //imprime contenido byte por byte
          printf("\n=========================================================\n");
          close(visor); //cierra el descriptor del archivo utilizado
        } 
        else
          printf("[ERROR] No se pudo leer/abrir %s\n", visualizado);
        printf("Ingrese los archivos que desea separados por comas (o enter si desea copiar todos):\n");
        getchar();
		fgets(archivillos,sizeof(archivillos),stdin);
        if (archivillos[0] == '\n') //fullarchivillos tiene una cadena con todos los nombres de los archivos separados por comas
          strncpy(archivillos, fullarchivillos, 511); //reemplaza archivillos con fullarchivillos
      	else
      		strtok(archivillos, "\n"); //elimina el \n que fgets introduce 
        string = strdup(archivillos); //clona archivillos y asigna memoria dinamica para la cadena
        while ((nombre_archivo = strsep( & string, ",")) != NULL) //en nombre_archivo guarda cada parte de la cadena
        { //hasta que encuentra un simbolo de coma, siguiendo hasta que la cadena termine
          fuente = open(nombre_archivo, O_RDONLY); //abre la fuente como solo lectura
          if (fuente != -1) //si fue posible abrir la fuente, procede
          {
            chdir(argv[2]); //cambia al directorio destino
            creat(nombre_archivo, 0755); //crea un archivo cualquiera con el mismo nombre
            destino = open(nombre_archivo, O_WRONLY | O_APPEND); //obtener descriptor del nuevo archivo
            while ((bits = read(fuente, buf, BUFFER_SZ)) > 0) //lee todo el archivo y guarda en bits la cantidad de bits que ha leido
			{
    			if (write(destino, buf, bits) != bits) //escribe en el archivo destino cierta cantidad de bits, y comprueba si se escribio todo
        			printf("[ERROR] No se pudo copiar todo el buffer\n");
        		else 
	                printf("[  OK ] %s copiado correctamente\n", nombre_archivo); //solo si copia y accede correctamente al archivo
			}
            close(destino);   close(fuente); //liberacion de descriptores
            chdir(argv[1]); //cambiar a directorio fuente
          } else
            printf("[ERROR] No existe (o no se pudo leer) '%s'\n", nombre_archivo);
        }
        free(buf); //liberar el buffer encargado de copiar despues de usarlo
        return (0);
      }
    } else
      printf("[ERROR] Alguna de las dos carpetas no existe.\n");
  }
}