#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "operadores.h"
#define SIZ_MAX     3

int main()
{
    float ass[9];
    float as[3][3];
    ObtenerMatCompartida(6666,ass);
    Ar1D_Ar2D(ass,as);
    ImpMat(as, 3,3,NULL,1,1,0);
    TerminarEspera(123);

    exit(0);
}


