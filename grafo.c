#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//Definiciones
#define TRUE 1
#define FALSE 0
#define INF 100000000000

typedef int BOOL;

BOOL *Marcado = NULL;
int **Matriz_costos = NULL;
//funciones muy utiles
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
void LecturaDeArchivo(char archivo[20])
{
	FILE *arch;
	int nodos,aristas,ni,nf,i,m,n;

	arch = fopen(archivo,"r");
	if (arch != NULL)
	{
		fscanf(arch,"%d",&nodos);
		fscanf(arch,"%d",&aristas);
		printf("El grafo tiene %d nodos y %d aristas.\n",nodos,aristas);
		Matriz_costos = DaMemoriaMatriz(nodos,nodos);
		fscanf(arch,"%d",&ni);
		fscanf(arch,"%d",&nf);
    for (i = 0; i < aristas; i++)
    {
      fscanf(arch,"%d",&m);
			fscanf(arch,"%d",&n);
			fscanf(arch,"%d",&Matriz_costos[m][n]);
    }
    Marcado = DaMemoriaArreglo(nodos);
		fclose(arch);
    // imprimr matriz de costo
    for (m = 0; m < nodos; m++)
    {
      for (n = 0; n < nodos; n++)
      {
        printf("%3d",Matriz_costos[m][n]);
      }
      printf("\n");
    }
	}
}
void main(int argc, char *argv[])
{
	LecturaDeArchivo(argv[1]);
}
