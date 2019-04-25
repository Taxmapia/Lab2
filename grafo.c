#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define TRUE 1
#define FALSE 0
#define INF 100000000000

typedef int BOOL;

BOOL *Marcado = NULL;
int **Grafo = NULL;


int *DaMemoriaArreglo(int n)
{
    int *aux, i;

    aux = (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
    {
        aux[i] = FALSE;
    }
    return aux;
}
int **DaMemoriaMatriz(int m, int n)
{
    int **aux, i, j;

    aux = (int **)malloc(m*sizeof(int *));
    for(i=0;i<m;i++)
    {
        aux[i] = (int *)malloc(n*sizeof(int));
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            aux[i][j] = 0;
        }
    }
    return aux;
}
void LecturaDeArchivo(char arch[50])
{
	FILE *arch;
	int nodos,aristas,ni,nf,i,j;

	arch = fopen(arch,"r");
	if (arch != NULL)
	{
		fscanf(arch,"%d",&nodos);
		fscanf(arch,"%d",&aristas);
		printf("El grafo tiene %d nodos y %d aristas.\n",nodos,aristas);
		Grafo = DaMemoriaMatriz(nodos,nodos)
		fscanf(arch,"%d",&ni);
		fscanf(arch,"%d",&nf);
		while(arch != EOF)
		{
			fscanf(arch,"%d",&i);
			fscanf(arch,"%d",&j);
			fscanf(arch,"%d",&Grafo[i][j]);
		}
		Marcado = DaMemoriaArreglo(nodos);
		fclose(arch);
	}	
}
void int main(int argc, char const *argv[])
{
	LecturaDeArchivo(argv[1]);
	return 0;
}