
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void clean_stdin();
int main(int argc, char *argv[])
{
    char archivillos[512], visualizado[512],fullarchivillos[512], contenido, *string, *nombre_archivo; int i,visor,fuente,destino,bits; void *buf = (char*) calloc(1000,sizeof(char));
    archivillos[0] = '\0', fullarchivillos[0]='\0';
if (argv[1]==NULL || argv[2]==NULL)
{
    printf("[ERROR] Uso: ./p4 (ruta absoluta de archivos a visualizar) (ruta absuolta destino de archivos a copiar)\n");
    exit(-1);
}
else
{
DIR* carpeta = opendir(argv[1]); //Se verifica si ya existe el directorio
DIR* carpetadestino = opendir(argv[2]);
if (carpeta&&carpetadestino)
{
    printf("[  OK ] Directorio encontrado\n"); //Salir si ya existe el directorio
    DIR *d;
    struct dirent *carpeta;
    d = opendir(argv[1]); //Para abrir el directorio en el que se encuentra
    if (d) {
    while ((carpeta = readdir(d)) != NULL) { //lista todo hasta que sea el 'fin' de la carpeta
      if (carpeta->d_type == DT_REG)
        { //omite cualquier cosa que no sea un archivo regular
        printf("%s\n", carpeta->d_name); //imprime todos los archivos dentro de la carpeta
        //snprintf(fullarchivillos, sizeof(fullarchivillos),"%s,",carpeta->d_name);
        strcat(fullarchivillos,carpeta->d_name);
        strcat(fullarchivillos,",");
        }
    }   i = strlen(fullarchivillos);//Para obtener la longitud de toda la cadena
        fullarchivillos[i - 1] = '\0'; //Quitar la ultima coma
        closedir(d); //cierra el descriptor de la carpeta
        chdir(argv[1]); //cambia al directorio de la primera carpeta
        printf("\nIngrese el archivo del cual desea visualizar su contenido:\n");
        scanf("%s",&visualizado);
            if ((visor = open(visualizado, O_RDONLY)) >= 0) //abre el archivo como solo lectura
            {
                printf("=========================%s========================\n",visualizado);
                while (read(visor, &contenido, 1) == 1) //descriptor, buffer a almacenar el contenido y cantidad de bytes a leer
                    putchar(contenido); //imprime contenido byte por byte
                printf("\n=========================================================\n");
                close(visor); //cierra el descriptor del archivo utilizado
            }
            else
                printf("[ERROR] No se pudo leer/abrir %s\n",visualizado);
        printf("\nIngrese los archivos que desea separados por comas (o 0 si desea copiar todos):\n");
        scanf("%s",&archivillos);
        if(archivillos[0]=='0')
            strncpy(archivillos, fullarchivillos, 511); //reemplaza archivillos con fullarchivillos
        clean_stdin(); //limpiar el buffer de entrada
        string = strdup(archivillos); //clona archivillos y asigna memoria para la cadena
            while((nombre_archivo = strsep(&string,",")) != NULL ) //en nombre_archivo guarda cada parte de la cadena
            { //hasta que encuentra un simbolo de coma, siguiendo hasta que la cadena termine
                fuente=open(nombre_archivo,O_RDONLY); //abre la fuente como solo lectura
                if(fuente!=-1) //si fue posible abrir la fuente, procede
                {
                    chdir(argv[2]); //cambia al directorio destino
                    creat(nombre_archivo,0755); //crea un archivo cualquiera con el mismo nombre
                    destino=open(nombre_archivo, O_WRONLY | O_APPEND); //obtener descriptor del nuevo archivo
                    while((bits=read(fuente,buf,1000)>0)) //escribe de 1000 en 1000 bits
                    {
                        if(write(destino,buf,1000)!=-1 && (access(nombre_archivo,0)==0))
                        printf("[  OK ] %s copiado correctamente\n",nombre_archivo); //solo si copia y accede correctamente al archivo
                    }   // copiado, se muestra "copiado correctamente"
                close(destino);     close(fuente);     //liberacion de descriptores
                chdir(argv[1]); //cambiar a directorio fuente
                }
                    else
                        printf("[ERROR] No existe (o no se pudo leer) '%s'\n",nombre_archivo);
                }
return(0);

}
}
else
    printf("[ERROR] Alguna de las dos carpetas no existe.\n");
}
}
void clean_stdin()
{
        int stdin_copy = dup(STDIN_FILENO);
        tcdrain(stdin_copy);
        tcflush(stdin_copy, TCIFLUSH);
        close(stdin_copy);
}