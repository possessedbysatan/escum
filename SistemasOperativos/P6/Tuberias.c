#include <stdlib.h>
#include <stdio.h> //El hijo multiplica y el nieto las suma
#include "operadores.h"
#define SIZ_MAX 10
int main()
{
    float matrizA[SIZ_MAX][SIZ_MAX],matrizB[SIZ_MAX][SIZ_MAX],InvA[SIZ_MAX][SIZ_MAX],InvB[SIZ_MAX][SIZ_MAX];
    int matrA[2],matrB[2], resSSum[2], resMMult[2];
    printf("Inserte datos (A):\n");
    InsEnMat(matrizA,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizA
    printf("Inserte datos (B):\n");
    InsEnMat(matrizB,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizA
    pipe(matrA); pipe(matrB); pipe(resSSum); pipe (resMMult);
        printf("Las dos matrices se comparten.\n");
    Matriz2Tuberia(matrizA,matrA);
    Matriz2Tuberia(matrizB,matrB);   
    
    if(fork()==0) //HIJO 1
    {
        float resMult[SIZ_MAX][SIZ_MAX],matrizAHijo[SIZ_MAX][SIZ_MAX],matrizBHijo[SIZ_MAX][SIZ_MAX];
        Tuberia2Matriz(matrA,matrizAHijo);
        Tuberia2Matriz(matrB,matrizBHijo);
        Multiplicar(matrizAHijo,matrizBHijo,resMult);
        Matriz2Tuberia(resMult,resMMult); //El resultado de la suma se guarda en el descriptor matrA, aunque 
        printf("[hijo] Inserte datos (A):\n"); //no importa el descriptor que se use
        InsEnMat(matrizAHijo,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizA
        printf("[hijo] Inserte datos (B):\n");
        InsEnMat(matrizBHijo,SIZ_MAX,SIZ_MAX); //Dialogos para insertar MatrizA
        Matriz2Tuberia(matrizAHijo,matrA);     //Escribir la nueva matriz A al descriptor
        Matriz2Tuberia(matrizBHijo,matrB);     //Escribir matrizB al otro descriptor
        if(fork()==0)
        {
            float resSum[SIZ_MAX][SIZ_MAX],matANieto[SIZ_MAX][SIZ_MAX],matBNieto[SIZ_MAX][SIZ_MAX];
            Tuberia2Matriz(matrA,matANieto);    //Leer y guardar en una matriz desde la tuberia
            Tuberia2Matriz(matrB,matBNieto);    //Leer y guardar en una matriz desde la tuberia
            SumaOResta(matANieto,matBNieto,resSum,1);   //sumarlas
            Matriz2Tuberia(resSum,resSSum);             //guardarlas en el otro descriptor (matA es para la multiplicacion)
            exit(0);
        }
        wait(0); exit(0);
    }
    wait(0);
    system("clear");
    Tuberia2Matriz(resMMult,matrizA);
    Tuberia2Matriz(resSSum,matrizB);
    printf("Resultado multiplicacion: \n");
    ImpMat(matrizA,NULL,1,1,0);
    printf("Resultado suma: \n");
    ImpMat(matrizB,NULL,1,1,0);
    if(determ(matrizA,SIZ_MAX)!=0)
    {
        TreInversaCaller(matrizA,InvA,SIZ_MAX);
        printf("Inversa de la multiplicacion: \n");
        ImpMat(InvA,"Inversa de la multiplicacionTub.txt",0,0,0);
    }
    else
        printf("[ERROR] La multiplicacion no fue L.I.\n");  
    if(determ(matrizB,SIZ_MAX)!=0)
    {
        TreInversaCaller(matrizB,InvB,SIZ_MAX);
        printf("Inversa de la suma:\n");
        ImpMat(InvB,"Inversa de la sumaTub.txt",0,0,0);
    }
    else
        printf("[ERROR] La suma no fue L.I.\n");
} 