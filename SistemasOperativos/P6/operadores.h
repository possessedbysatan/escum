#include<stdio.h>
#include<curses.h>
#include<math.h>
#include<string.h>
#include<pthread.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/syscall.h>


#define SIZ_MAX 3
float determ(float a[SIZ_MAX][SIZ_MAX], float tam);
// int < determ(matrizA, tamMatriz)
void TreInversaCaller(float [SIZ_MAX][SIZ_MAX], float dest[SIZ_MAX][SIZ_MAX], float);
// void < TreInversaCaller(matrizOrigen, matrizDestino, tamMatriz)
void treinversa(float [][SIZ_MAX], float [][SIZ_MAX], float dest[][SIZ_MAX], float); //llamada indirecta
void ImpMat(float matrix[SIZ_MAX][SIZ_MAX], char* nombre, int nodecim, int nofile, int nomostrar);
// void < ImpMatriz (matrizAImprimir, TamFila, TamColumna, EtiquetaParaArchivo, NoMostrarDecimales(1), NoImprimirA-Archivo(1), NoMostrar(1))
void InsEnMat(float matrix[SIZ_MAX][SIZ_MAX], int row, int column);
// void < InsertarEnMatriz (matrizAInsertar, TamFila, TamColumna)
void SumaOResta (float matrix[SIZ_MAX][SIZ_MAX], float matrix2[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX], int pain);
// void < SumaOResta (matrizA, matrizB, matrizDestino,FlagSuma(1))
void Transpuesta(float matrix[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX], int row, int column);
// void < transpuesta(matrizOrigen, matrizDestino, TamFila, TamColumna)
void Multiplicar(float matrix[SIZ_MAX][SIZ_MAX], float matrix2[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX]);
// void < Multiplicar(matrizA, matrizB, matrizDestino)
void CargarEnArreglo(char *NombreArchivo, float matrix[SIZ_MAX][SIZ_MAX],int tam, int skiprows);
// void < CargarEnArreglo("nombreArchivo",matrizDestino, TamFila, TamColumna, SaltarNLineas)
int ObtenerIDHilo(void );
// Devuelve el ID del hilo.
void CompartirMat (float matrizOrigen[SIZ_MAX][SIZ_MAX],int key);
//void CompartirMat (Matriz1D Origen,llave);
void ObtenerMatCompartida(int key, float matrizDestino[SIZ_MAX][SIZ_MAX]);
//void ObtenerMatCompartida(llave, matriz1D-Destino)
void CrearEspera(int key);
//void CrearEspera(llave)
void TerminarEspera(int key);
//void CrearEspera(llave);
void EliminarDeMemoria (int key);
//void EliminarDeMemoria (llave)
void CopiarMatriz(float matrizOrigen[SIZ_MAX][SIZ_MAX],float matrizDestino[SIZ_MAX][SIZ_MAX]);
//void CopiarMatriz(matrizOrigen,matrizDestino)
float determ(float a[SIZ_MAX][SIZ_MAX], float tam)
{
  float s = 1, det = 0, b[SIZ_MAX][SIZ_MAX];
  int i, j, m, n, c;
  if (tam == 1)
    {
     return (a[0][0]);
    }
  else
    {
     det = 0;
     for (c = 0; c < tam; c++)
       {
        m = 0;
        n = 0;
        for (i = 0;i < tam; i++)
          {
            for (j = 0 ;j < tam; j++)
              {
                b[i][j] = 0;
                if (i != 0 && j != c)
                 {
                   b[m][n] = a[i][j];
                   if (n < (tam - 2))
                    n++;
                   else
                    {
                     n = 0;
                     m++;
                     }
                }
               }
             }
          det = det + s * (a[0][c] * determ(b, tam - 1));
          s = -1 * s;
          }
    }
    return (det);
}
void TreInversaCaller(float num[SIZ_MAX][SIZ_MAX],float dest[SIZ_MAX][SIZ_MAX], float f)
{
 float b[SIZ_MAX][SIZ_MAX], fac[SIZ_MAX][SIZ_MAX];
 int p, q, m, n, i, j;
 for (q = 0;q < f; q++)
 {
   for (p = 0;p < f; p++)
    {
     m = 0;
     n = 0;
     for (i = 0;i < f; i++)
     {
       for (j = 0;j < f; j++)
        {
          if (i != q && j != p)
          {
            b[m][n] = num[i][j];
            if (n < (f - 2))
             n++;
            else
             {
               n = 0;
               m++;
               }
            }
        }
      }
      fac[q][p] = pow(-1, q + p) * determ(b, f - 1);
    }
  }
  treinversa(num, fac, dest, f);
}
void treinversa(float num[SIZ_MAX][SIZ_MAX], float fac[SIZ_MAX][SIZ_MAX], float dest[SIZ_MAX][SIZ_MAX], float r)
{
  int i, j;
  float b[SIZ_MAX][SIZ_MAX], d;
  for (i = 0;i < r; i++)
     for (j = 0;j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
  d = determ(num, r);
for (i = 0;i < r; i++)
    {
        for (j = 0;j < r; j++)
        {
            dest[i][j] = b[i][j] / d;
        }
    }
 }
 void InsEnMat (float matrix[SIZ_MAX][SIZ_MAX], int row, int column)
{
    int i, j;
    for (i=0;i<row;i++)
    {

        for (j=0;j<column;j++)
        {
            printf ("POS [%d | %d] ", i+1, j+1);
            scanf  ("%f", &matrix[i][j]);
        }
    }
}
void ImpMat (float matrix[SIZ_MAX][SIZ_MAX], char* operacion, int nodecim, int nofile, int nomostrar)
{
    int i, j;
    FILE *NuevoArchivo;
    if(nofile!=1)
      NuevoArchivo = fopen(operacion, "w");
    if(NuevoArchivo!=NULL && nofile!=1)
      fprintf(NuevoArchivo,"%s \n",operacion);
    for(i=0;i<SIZ_MAX;i++)
      {
          for(j=0;j<SIZ_MAX;j++)
          {
              if(nodecim==1)
              {
              if(nomostrar!=1)
                printf("%.0lf ", matrix[i][j]);
              if(NuevoArchivo!=NULL && nofile!=1)
                fprintf(NuevoArchivo,"%.0lf ",matrix[i][j]);
              }
              else
              {
              if(nomostrar!=1)
                printf("%.2lf ", matrix[i][j]);
              if(NuevoArchivo!=NULL && nofile!=1)
                fprintf(NuevoArchivo,"%.2lf ",matrix[i][j]);
              }
          }
          if(nomostrar!=1)
            printf("\n");
          if(NuevoArchivo!=NULL && nofile!=1)
            fprintf(NuevoArchivo,"\n");
      }
      if(NuevoArchivo!=NULL && nofile!=1)
        fclose(NuevoArchivo);
  }
void SumaOResta (float matrix[SIZ_MAX][SIZ_MAX], float matrix2[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX], int pain)
{
    int i;
    int j;
    for(i=0;i<SIZ_MAX;i++)
        for(j=0;j<SIZ_MAX;j++)
        {
          if(pain==1)
            matrixDest[i][j]=matrix[i][j]+matrix2[i][j];
          else
            matrixDest[i][j]=matrix[i][j]-matrix2[i][j];
        }
}
void Transpuesta(float matrix[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX], int row, int column)
{
    int i;
    int j;
    for(i=0;i<row;i++)
        for(j=0;j<column;j++)
        {
            matrixDest[i][j]=matrix[j][i];
        }
}
void Multiplicar(float matrix[SIZ_MAX][SIZ_MAX], float matrix2[SIZ_MAX][SIZ_MAX], float matrixDest[SIZ_MAX][SIZ_MAX])
{
    int i, j, k;
    for (i=0;i<SIZ_MAX; i++)
    {
        for (j=0;j<SIZ_MAX;j++)
        {
            matrixDest[i][j]=0;
            for (k = 0; k < SIZ_MAX; k++)
                matrixDest[i][j]+=matrix[i][k]*matrix2[k][j];
        }
    } 
}
void LeerArchivos(char *NombreArchivo)
{
    char c; FILE *PTRNomArch;
    PTRNomArch = fopen(NombreArchivo, "r");
    if (PTRNomArch == NULL)
    {
        printf("No se pudo abrir el archivo %s\n",NombreArchivo);
        exit(0);
    }
    c = fgetc(PTRNomArch);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(PTRNomArch);
    }
    fclose(PTRNomArch);
}
 void CargarEnArreglo(char *NombreArchivo, float matrix[SIZ_MAX][SIZ_MAX], int tam, int skiprows)
{
    int counter=0, numberRead=0, i, j,cont=0;
    int array[100];
    FILE *PTRNomArch;
    PTRNomArch = fopen(NombreArchivo, "r");
    if (PTRNomArch == NULL)
    {
        printf("No se pudo abrir el archivo %s\n",NombreArchivo);
        exit(0);
    }
    char buffer[100]; //la primera linea se asume que es de 100    
    if (skiprows>0)
      for(int rowskipped=0;rowskipped<skiprows;rowskipped++)
        fgets(buffer, 100, PTRNomArch);
    char arr[666];
    char* ptr;
    fread(arr , 1,sizeof arr , PTRNomArch);
    ptr = strtok(arr , " ");
    while(ptr)
    {
      array[counter++] = strtol(ptr , NULL , 10);
      ++numberRead;
      ptr = strtok(NULL , " ");
    }
    for(i=0;i<tam;i++)
      for(j=0;j<tam;j++)
      {
        matrix[i][j]=(double)array[cont++];
//        cont++;
      }       
    fclose(PTRNomArch);
}         
void CompartirMat (float matrizOrigen[SIZ_MAX][SIZ_MAX],int key)
{
  float matrix[SIZ_MAX*SIZ_MAX];
  float *matrizComp;
  int shmid;
   if ((shmid = shmget((key_t) key, sizeof matrix[SIZ_MAX*SIZ_MAX], IPC_CREAT | 0666)) < 0) {
        printf("Error al crear el segmento de memoria.");
        exit(1);
    }
    
    if ((matrizComp = shmat(shmid, NULL, 0)) == (void *) -1) {
        printf("Error al obtener la memoria compartida");
        exit(1);
    }
  int cont=0; 
  for(int i=0;i<SIZ_MAX;i++) //Este ciclo sirve para
    for(int j=0;j<SIZ_MAX;j++) //Convertir una matriz bidimensional a una 
      {                        //matriz lineal, que luego se va compartir
        matrix[cont++]=matrizOrigen[i][j]; 
      }

  float *auxbkp=matrizComp; //Apuntador auxiliar
  for (int i=0;i<SIZ_MAX*SIZ_MAX;i++) //Usa los valores el arreglo lineal...
  {                                   //...y los guarda en el contenido del apuntador.
    *(auxbkp++)=matrix[i]; //Ir a la siguiente region
  }
  //printf("[OK/CML] key: %d\n",key);
}
void ObtenerMatCompartida(int key, float matrizDestino[SIZ_MAX][SIZ_MAX])
{
  int shmid; 
  float *matrizComp;
  float matrix[SIZ_MAX*SIZ_MAX];
  if ((shmid = shmget((key_t) key, sizeof matrix[SIZ_MAX*SIZ_MAX], IPC_CREAT | 0666)) < 0) {
        printf("Error al crear el segmento de memoria.");
        exit(1);
    }
 // printf("[INFO/ObMatCmp] key: %d\n",key);
    if ((matrizComp = shmat(shmid, NULL, 0)) == (void *) -1) {
        printf("Error al obtener la memoria compartida");
        exit(1);
    }
      float *auxbkp=matrizComp; //Apuntador auxiliar
    for(int i=0;i<SIZ_MAX*SIZ_MAX;i++)
    {
      matrix[i]=*(auxbkp++); //En la matriz lineal se guarda el contenido
    }                        //del apuntador, y se incrementa el apuntador
  int cont=0;
  for(int i=0;i<SIZ_MAX;i++) //Estos ciclos son para transformar la matriz
    for(int j=0;j<SIZ_MAX;j++)//lineal a una matriz bidimensional
      {                       //para facilitar el uso de la funcion.
        matrizDestino[i][j]=matrix[cont++];
      }
}
void CrearEspera(int key)
{
  int ref[1]; //Esta funcion sirve como semaforo si es que se utiliza
  int *matrizComp; //Un cliente y servidor en procesos separados.
  int shmid;
   if ((shmid = shmget((key_t) key, sizeof ref[1], IPC_CREAT | 0666)) < 0) {
        printf("Error al crear el segmento de memoria.");
        exit(1);
    }
    if ((matrizComp = shmat(shmid, NULL, 0)) == (void *) -1) {
        printf("Error al obtener la memoria compartida");
        exit(1);
    }
    printf("[INFO/WAIT] esperando unlock: %d\n",key);
    while (*matrizComp != key)
        sleep(1);
    if(*matrizComp==key)
      printf("[INFO/WAIT] unlock recibido: %d\n",key);
}
void TerminarEspera(int key)
{
  int ref[1]; //Esta funcion sirve para controlar el semaforo
  int *matrizComp; //Si es que se utiliza cliente y servidor.
  int shmid;
   if ((shmid = shmget((key_t) key, sizeof ref[1], IPC_CREAT | 0666)) < 0) {
        printf("Error al crear el segmento de memoria.");
        exit(1);
    }
    if ((matrizComp = shmat(shmid, NULL, 0)) == (void *) -1) {
        printf("Error al obtener la memoria compartida");
        exit(1);
    }   
    *matrizComp=key;
    if(shmctl(shmid, IPC_RMID, NULL)!=-1)
      printf("[INFO/TE] liberando: %d\n",key);
    else
      printf("[ERROR] No existe/no se pudo liberar %d\n",key);
}
void EliminarDeMemoria (int key)
{
  float ref[SIZ_MAX*SIZ_MAX]; //Sirve para eliminar los datos que podrian
  int shmid;                  //permanecer en memoria y causar conflictos.
   if ((shmid = shmget((key_t) key, sizeof ref[SIZ_MAX*SIZ_MAX], IPC_CREAT | 0666)) < 0) {
        printf("Error al crear el segmento de memoria.");
        exit(1);
    }
  if(shmctl(shmid, IPC_RMID, NULL)!=-1)
    printf("[INFO/EM] %d eliminado de memoria\n",key);
}
int ObtenerIDHilo(void ){
    pid_t threadid = syscall(SYS_gettid); 
    return threadid; //Sirve para obtener el identificador del hilo
}
void CopiarMatriz(float matrizOrigen[SIZ_MAX][SIZ_MAX],float matrizDestino[SIZ_MAX][SIZ_MAX]){
  for(int i=0;i<SIZ_MAX;i++)
    for(int j=0;j<SIZ_MAX;j++)
      matrizDestino[i][j]=matrizOrigen[i][j];
}