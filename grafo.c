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
int nodos;
int aristas;
int ni;
int nf;
int **Matriz=NULL;
//funciones muy utiles
void Lectura_Archivo()
{
    FILE *arch;
    char archivo[100];
    int var = 0, m, n, i, j, costo;

    while(condicion == 0)
    {
        printf("Instancia: ");
        scanf("%s", archivo);
        arch = fopen(archivo,"r");

        if(archivo!=NULL)
        {
            fscanf(arch, "%d", &nodos);
            fscanf(arch, "%d", &aristas);
            fscanf(arch, "%d", &ni);
            fscanf(arch, "%d", &nf);

            //En esta parte se le asigna un espacio de memoria a la matriz dinamica
            Matriz = (int **)malloc(nodos*sizeof(int));
            for(n=0; n<nodos; n++)
            {
                Matriz[n] = (int *) malloc(nodos*sizeof(int));
            }
            if(Matriz == NULL)
            {
                printf("NO hay suficiente espacio en memoria\n\n");
                var++;
            }

            //Aca se rellena la matriz con 0 para que no sea una matriz NULL
            for(n=0;n<nodos;n++)
            {
                for(m=0;m<nodos;m++)
                    Matriz[n][m]=0;
            }

            //Se carga la matriz con los datos del archivo que se va a leer
            for(n=0;n<aristas; n++)
            {
                fscanf(arch, "%d", &i);
                fscanf(arch, "%d", &j);
                fscanf(arch, "%d", &var);
                Matriz[i][j] = var;
            }
            fclose(archivo);
        }
        else
        {
            printf("ERROR: <Archivo fallido o no encontrado.>\n\n");
            var++;
        }
        var++;
    }

   //Se imprime la matriz para darle una idea al usuario
   printf("\n");
   for(m=0; m<nodos; m++)
   {
       for(n=0; n<nodos; n++)
       {
          printf("%2d", Matriz[m][n]);
       }
       printf("\n");
   }
}
void main()
{
	LecturaDeArchivo();
}
