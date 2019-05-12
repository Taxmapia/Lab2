//librerias
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//definiciones
#define TRUE 1
#define FALSE 0
#define INF 3000000

//variables locales
typedef int BOOL;
int **Grafo = NULL;
BOOL *Visitado = NULL;
int nodos;
int r;
int v0;
int vf;
int t = 0;
int cm; //costo minimo

//asignacion de espacio en la memoria para la matriz dinamica
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

//crea un arreglo de largo n con ceros
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

//lectura de archivo
void LecturaDeArchivo()
{
    FILE *arch;
    char archivo[45];
    int aristas,costo;
    int i, j;
    int a = 0;

    printf("Ingrese nombre del archivo: ");

    while (a == 0)
    {
        scanf("%s",archivo);

        arch = fopen(archivo,"r");
        if (arch == NULL)
        {
            printf("\nError al abrir el archivo texto\n");
            printf("\nIngrese nombre del archivo: ");
        }
        else
        {
            a++;
        }
    }
    fscanf(arch,"%d", &nodos);
    fscanf(arch,"%d", &aristas);
    fscanf(arch,"%d",&v0);
    fscanf(arch,"%d",&vf);

    Grafo = DaMemoriaMatriz(nodos,nodos);
    for(r=0; r<aristas; r++)
            {
                fscanf(arch, "%d", &i);
                fscanf(arch, "%d", &j);
                fscanf(arch, "%d", &costo);
                Grafo[i][j] = costo;
            }

    Visitado = DaMemoriaArreglo(nodos);
    fclose(arch);
}
//inicializa los visitados en false a todos
void InicializaVisitados()
{
    int i;
    for(i=0;i<nodos;i++)
    {
        Visitado[i] = FALSE;
    }
}
//Imprecion de camino
void ImprimeCaminos(int *NodoAnterior, int *Costo, int nodos, int v0, int vf)
{
    int *Camino, i, j, nodo;

    Camino = DaMemoriaArreglo(nodos);

    for(i=0;i<nodos;i++)
    {
        if (i != v0)
        {
            j = 0;
            Camino[j] = i;
            j++;
            nodo = NodoAnterior[i];
            while(nodo != v0)
            {
                Camino[j] = nodo;
                j++;
                nodo = NodoAnterior[nodo];
            }
            Camino[j] = nodo;

            if(Costo[i] != INF)
            {
                 if( i == vf)
                {
                  printf("\n%2d\n", Costo[i]);

                  while (j >= 0)
                  {
                      printf("%2d", Camino[j]);
                      j--;
                  }
                }
            }
            else
            {
                printf("\n-1");
                return;
            }
        }
    }
}
//cantidad de nodos no visitados
int NumeroNodosSinVisitar(int *Visitado, int nodos)
{
    int i, cont;

    i = 0;
    cont = 0;

    while (i < nodos)
    {
        if (!Visitado[i])
        {
            cont++;
        }
        i++;
    }
   return cont;
}
//Nodo de menor costo
int NodoMinimoCostoSinVisitar(int *Visitado, int *Costo, int nodos)
{
    int i, nodo, minimo;

    i = 0;
    while (Visitado[i])
    {
        i++;
    }

    minimo = Costo[i];
    nodo = i;

    i++;
    while(i < nodos)
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
//DIJKSTRA, determiona el camino de costo minimo del grafo ingresado
void DIJKSTRA(int **Grafo, int nodos, int v0)
{
    BOOL *Visitado;
    int i, j;
    int w = v0;
    int *Costo;
    int *NodoAnterior;

    Visitado = DaMemoriaArreglo(nodos);
    Costo = DaMemoriaArreglo(nodos);
    NodoAnterior = DaMemoriaArreglo(nodos);

    Visitado[v0] = TRUE;
    for(i=0;i<nodos;i++)
    {
        if (Grafo[v0][i] == 0)
        {
            Costo[i] = INF;
        }
        else
        {
            Costo[i] = Grafo[v0][i];
        }
        NodoAnterior[i] = v0;
    }
    while (NumeroNodosSinVisitar(Visitado, nodos)>1)
    {
        w = NodoMinimoCostoSinVisitar(Visitado, Costo, nodos);
        Visitado[w] = TRUE;
        for(j=0;j<nodos;j++)
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
    //desde aca calcula el camino casi mas corto y si no retorna un -1
      if(t==0)
    {
        cm = Costo[vf];
        if (cm == INF)
        {
          printf("\n-1\n");
          return;
        }
    }
    t++;
    if(t!=0&&cm==Costo[vf])
    {
        Grafo[NodoAnterior[vf]][vf] = 0;
        DIJKSTRA(Grafo, nodos, v0);
    }
    else
    {
        ImprimeCaminos(NodoAnterior, Costo, nodos, v0, vf);
    }
}
//Main :)
int main()
{
  LecturaDeArchivo();
  InicializaVisitados();
  DIJKSTRA(Grafo, nodos, v0);
  printf("\n");
  return 0;
}
