#include <stdio.h>
void asteriscos(int kek, FILE *bepis);
void espacios(int kek, FILE *bepis);
void endline(FILE *bepis);
int main()
{
	int cantidad,i,j,k=0,espaciosdentro=1,altura=0,espaciosmedio=0,l=0,em_aux,ondskapt; FILE *archtexto = fopen("rombos_chidoris.txt", "w");
	printf("Introduzca cantidad impar de asteriscos mayor o igual que 5: ");
	scanf("%d",&cantidad);
	altura=cantidad/2;
	espaciosmedio=(cantidad-1);
	em_aux=espaciosmedio-2;
	for (i=0;i<altura+1;i++)
	{
		for(j=0;j<altura-i;j++) //imprime los espacios antes de la linea principal
			espacios(1,archtexto);
		if(i==0) //funcion que se encarga de imprimir solo la primera linea
		{
			asteriscos(1,archtexto); 
			espacios(espaciosmedio,archtexto);
			asteriscos(1,archtexto);
		}
		if(i!=0 && i<altura)
		{
			asteriscos(1,archtexto); //linea de asteriscos izquierda, rombo vacio
			espacios(espaciosdentro,archtexto); //espacios dentro del rombo vacio
			espaciosdentro+=2; //aumento de 2 en 2 para el espacio
			asteriscos(1,archtexto); //linea de asteriscos derecha, rombo vacio
			espacios(em_aux,archtexto); //espacio entre rombos
			em_aux-=2; //decremento de 2 en 2 para el espacio
			asteriscos(espaciosdentro,archtexto); //imprime el rombo derecho (+2 agregados)
		} //imprime la linea principal 
		if(i==altura)
			asteriscos(cantidad*2,archtexto);
		endline(archtexto);
	}
	espaciosdentro=espaciosdentro-2; em_aux=2; //se resta 2 porque el ultimo valor guardado tenia un 2 agregado
	for(i=0;i<altura;i++)  //em_aux empieza en 2 porque la base de espacios entre rombos es siempre es multiplo de 2
		{
			espacios(i+1,archtexto); //espacios al principio del rombo vacio
			asteriscos(1,archtexto); //linea de asteriscos izquierda, rombo vacio
			if (i!=altura-1)
			{
				espacios(espaciosdentro,archtexto); //espacios dentro del rombo vacio
				espaciosdentro-=2; //restar 2 a los espacios dentro - rombo vacio
				asteriscos(1,archtexto); //linea de asteriscos derecha, rombo vacio
				espacios(em_aux,archtexto); //espacio entre rombos
				em_aux=em_aux+2; //aumento de 2 en 2 para el espacio
				asteriscos(espaciosdentro+4,archtexto); // +2 reales por la resta @44, asterisco izq y derecho
			}
			else //punta del rombo inferior derecho 
				{
					espacios(cantidad-1,archtexto);
					asteriscos(1,archtexto);
				}
			endline(archtexto);
		}
		fclose(archtexto);
		printf("Teclee 1 para eliminar el archivo de texto con los rombos: ");
		scanf("%d",&ondskapt);
		if (ondskapt==1)
			if (remove("rombos_chidoris.txt")==0)
				printf("NOICE.\n");
}
void asteriscos(int kek, FILE *bepis)
{
	int i;
	for(i=0;i<kek;i++)
	{
		printf("*");
		fprintf(bepis, "*");
	}
}
void espacios(int kek, FILE *bepis)
{
	int i;
	for(i=0;i<kek;i++)
	{
		printf(" ");
		fprintf(bepis," ");
	}
}
void endline(FILE *bepis)
{
	printf("\n");
	fprintf(bepis, "\n");
}