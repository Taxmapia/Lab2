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

BOOL *Visitado = NULL;
int nodos;
int aristas;
int v0;
int vf;
int **Matriz=NULL;

//funciones muy útiles
int *DaMemoriaArreglo(int nodos)
{
  int *aux, i;

  aux = (int *)malloc(n*sizeof(int));
  for(i=0;i<n;i++)
  {
      aux[i] = FALSE;
  }
  return aux;
}
int NodosSinVisitar(int *Visitado, int nodos)
{
  int i, cont = 0;

  for (i = 0; i < n; i++)
  {
    if (!Visitado[i])
    {
      cont++;
    }
  }
  return cont;
}
int NodoCostoMinimoSinVisitar(int *Visitado, int *Costo, int nodos)
{
    int i, nodo, minimo;

    i = 0;
    while (Visitado[i]){
        i++;
    }

    minimo = Costo[i];
    nodo = i;

    i++;
    while(i < n)
    {
        if (!Visitado[i])
        {
            if (Costo[i] < minimo)
            {
                minimo = Costo[i];
                nodo = i;
            }
        }
        i++;
    }
    return nodo;
}
//Lectura de archivo
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
          fscanf(arch, "%d", &v0);
          fscanf(arch, "%d", &vf);

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
            {
              Matriz[n][m]=0;
            }
          }

          //Se carga la matriz con los datos del archivo que se va a leer
          for(n=0;n<aristas; n++)
          {
            fscanf(arch, "%d", &i);
            fscanf(arch, "%d", &j);
            fscanf(arch, "%d", &var);
            Matriz[i][j] = var;
          }
          Visitado = DaMemoriaArreglo(nodos);
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
//DIJKSTRA
void DIJKSTRA(int **Grafo, int nodos, int v0)
{
  //Variables y punteros
    BOOL *Visitado;
    int *Costo;
    int *NodoAnterior;
    int i, j, w=v0;
    Visitado = DaMemoriaArreglo(n);
    Costo = DaMemoriaArreglo(n);
    NodoAnterior = DaMemoriaArreglo(n);

    Visitado[w] = TRUE; //se marca como visitado el nodo v0
    for(i=0;i<n;i++)
    {
      if (Grafo[v0][i] == 0) //si no estan conectados se declara como infinito
      {
        Costo[i] = inf;
      }
      else //si estan conectados se asigna el costo
      {
        Costo[i] = Grafo[v0][i];
      }
      NodoAnterior[i] = v0;
    }
    while (NodosSinVisitar(Visitado, n)>1)
    {
      w = NodoCostoMinimoSinVisitar(Visitado, Costo, n);
      Visitado[w] = TRUE;
      for(j=0;j<n;j++)
      {
        if ((Grafo[w][j] != 0) && (!Visitado[j]))
        {
          if (Costo[w] + Grafo[w][j] < Costo[j])
          {
            NodoAnterior[j] = w;
            Costo[j] = Costo[w] + Grafo[w][j];
          }
        }
      }
    }
    ImprimeCaminos(NodoAnterior, Costo, n, v0);
}
void main()
{
	LecturaDeArchivo();
  InicializaVisitados();
  printf("\n\n\tIngrese nodo inicial para buscar los caminos en el grafo (entre 0 y %d): ", n-1);
  scanf("%d", &v0);
  printf("\n\n\tLos caminos son: ");
  DIJKSTRA(Matriz, n, v0);
}
