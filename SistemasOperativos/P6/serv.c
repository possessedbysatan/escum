#include <stdlib.h>
#include <stdio.h>
#include "operadores.h"
#define SIZ_MAX 3
int main()
{
    float matrizA[SIZ_MAX][SIZ_MAX],matrizB[SIZ_MAX][SIZ_MAX],resultadoSum[SIZ_MAX][SIZ_MAX],resultadoMult[SIZ_MAX][SIZ_MAX],InvA[SIZ_MAX][SIZ_MAX],InvB[SIZ_MAX][SIZ_MAX];
    printf("Inserte datos (A):\n");
    InsEnMat(matrizA,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizA
    CompartirMat(matrizA,1234); //Compartir "matrizA"
    printf("Inserte datos (B):\n");
    InsEnMat(matrizB,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizB
    CompartirMat(matrizB,1235); //Compartir "matrizB"
    if(fork()==0) //HIJO 1
    {
        float A[SIZ_MAX][SIZ_MAX],B[SIZ_MAX][SIZ_MAX],resMult[SIZ_MAX][SIZ_MAX],matHijoA[SIZ_MAX][SIZ_MAX],matHijoB[SIZ_MAX][SIZ_MAX]; 
        ObtenerMatCompartida(1234,A); //Obtiene la matriz A y la guarda en "A"
        ObtenerMatCompartida(1235,B); //Obtiene la matriz A y la guarda en "B"
        Multiplicar(A,B,resMult);
        CompartirMat(resMult,1236);
        printf("[hijo] Inserte datos (A)\n");
        InsEnMat(matHijoA,SIZ_MAX,SIZ_MAX); //Dialogos para insertar "matHijoA"
        CompartirMat(matHijoA,1237);        //Compartirlo con llave 1237
        printf("[hijo] Inserte datos (B)\n"); 
        InsEnMat(matHijoB,SIZ_MAX,SIZ_MAX); // Dialogos
        CompartirMat(matHijoB,1238);        //Compartir con llave 1238
        if(fork()==0)
        {   
            float reeeeSuma[SIZ_MAX][SIZ_MAX],aaa[SIZ_MAX][SIZ_MAX],bbb[SIZ_MAX][SIZ_MAX];
            ObtenerMatCompartida(1237,aaa); //Obtener lo que este con la llave 1237 y guardarlo en aaa
            ObtenerMatCompartida(1238,bbb); //Obtener y guardar en bbb
            SumaOResta(aaa,bbb,reeeeSuma,1);
            CompartirMat(reeeeSuma,1239);
            exit(0);
        }
        wait(0);
        exit(0);
    }
    wait(0);
    system("clear");
    ObtenerMatCompartida(1236,resultadoMult);
    ObtenerMatCompartida(1239,resultadoSum);
    printf("Resultado de la multiplicacion:\n");
    ImpMat(resultadoMult,NULL,1,1,0);
    printf("Resultado de la suma:\n");
    ImpMat(resultadoSum,NULL,1,1,0);    
    if(determ(resultadoMult,SIZ_MAX)!=0)
    {
        TreInversaCaller(resultadoMult,InvA,SIZ_MAX);
        printf("Inversa de la multiplicacion: \n");
        ImpMat(InvA,NULL,0,1,0);
    }
    else
        printf("[ERROR] La multiplicacion no fue L.I.\n");
    
    if(determ(resultadoSum,SIZ_MAX)!=0)
    {
        TreInversaCaller(resultadoSum,InvB,SIZ_MAX);
        printf("Inversa de la suma:\n");
        ImpMat(InvB,NULL,0,1,0);
    }
    else
        printf("[ERROR] La suma no fue L.I.\n");
    for(int i=1234;i<1240;i++)
        EliminarDeMemoria(i); //Eliminar de memoria las matrices
} 