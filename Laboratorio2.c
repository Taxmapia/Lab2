/*
  Nombre: Eduardo Javier Araya Pacheco
  Rut: 19.668.674-6
  Asignatura: Algoritmo y estructura de datos
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TRUE 1
#define FALSE 0
#define inf 3000000
/*Variables Globales*/
typedef int BOOL;
int **Grafo = NULL;
BOOL *Visitado = NULL;
int n,m,inicial_nodo,final_nodo,p = 1,valor_minimo;
/*Crea una matriz y la rellena con ceros*/
int **DaMemoriaMatriz(int m, int n)
{
    int **aux, i, j;

    aux = (int **)malloc(m*sizeof(int *));
    for(i=0;i<m;i++)
        aux[i] = (int *)malloc(n*sizeof(int));
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            aux[i][j] = 0;
    return aux;
}
/*Crea un arreglo y rellena con ceros*/
int *DaMemoriaArreglo(int n)
{
    int *aux, i;

    aux = (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        aux[i] = FALSE;
    return aux;
}
/*Lectura de archivo*/
void leer_archivo()
{
    /* Manejo de archivos*/
    FILE *archivo;
    char nomarchivo[50];
    int nodos,aristas,inicio_nodo,valor;
    int i, j;
    int c = 0;

    printf("Ingrese nombre del archivo: ");
    /*Ciclo que abre el archivo*/
    while (c == 0)
    {
        scanf("%s",nomarchivo);
        /*Abrir el archivo*/
        archivo = fopen(nomarchivo,"r");
        if (archivo == NULL)
        {
            printf("\nError al abrir el archivo texto\n");
            printf("\nIngrese nombre del archivo: ");
        }
        else
        {
            c++;
        }
    }
    /*Numero de nodos*/
    fscanf(archivo,"%d", &n);
    /*Número de aristas*/
    fscanf(archivo,"%d", &aristas);
    /*El nodo de inicio*/
    fscanf(archivo,"%d",&inicio_nodo);
    /*El nodo de termino*/
    fscanf(archivo,"%d",&final_nodo);

    Grafo = DaMemoriaMatriz(n,n);
    for(m=0; m<aristas; m++)
            {
                fscanf(archivo, "%d", &i);
                fscanf(archivo, "%d", &j);
                fscanf(archivo, "%d", &valor);
                Grafo[i][j] = valor;
            }

    Visitado = DaMemoriaArreglo(n);
    /*cerrar el archivo*/
    fclose(archivo);
}
/*Función que inicializa visitados en false*/
void InicializaVisitados()
{
    int i;
    for(i=0;i<n;i++)
        Visitado[i] = FALSE;
}
/*Funcion que imprime camino en este laboratorio imprimira el camino casi mas corto*/
void ImprimeCaminos(int *NodoAnterior, int *Valor, int n, int inicial_nodo,int final_nodo)
{
    int *Camino, i, j, nodo;

    Camino = DaMemoriaArreglo(n);

    for(i=0;i<n;i++)
    {
        if (i != inicial_nodo)
        {
            j = 0;
            Camino[j] = i;
            j++;
            nodo = NodoAnterior[i];
            while(nodo != inicial_nodo)
            {
                Camino[j] = nodo;
                j++;
                nodo = NodoAnterior[nodo];
            }
            Camino[j] = nodo;

            if(Valor[i]!=inf)
            {
                 if(i==final_nodo)
                {
                  printf("\n%3d\n", Valor[i]);

                while (j >= 0)
                {
                    printf("%3d", Camino[j]);
                    j--;
                }
                }
            }
            else
            {
                printf("\n-1");
            }

        }
    }
}
/*Indica el numero de nodos restasntes sin visitar*/
int NumeroNodosSinVisitar(int *Visitado, int n)
{
    int i, cont;

    i = 0;
    cont = 0;

    while (i < n)
    {
        if (!Visitado[i]){
            cont++;
        }
        i++;
    }
   return cont;
}
/*Verifica el costo minimo del nodo sin visitar*/
int NodoMinimoCostoSinVisitar(int *Visitado, int *Valor, int n)
{
    int i, nodo, minimo;

    i = 0;
    while (Visitado[i]){
        i++;
    }

    minimo = Valor[i];
    nodo = i;

    i++;
    while(i < n)
    {
        if (!Visitado[i])
        {
            if (Valor[i] < minimo)
            {
                minimo = Valor[i];
                nodo = i;
            }
        }
        i++;
    }
    return nodo;
}
/*Calcula el camino minimo de un grafo*/
void DIJKSTRA(int **Grafo, int n, int inicial_nodo)
{
    BOOL *Visitado;
    int i, j, w=inicial_nodo;

    int *Valor;
    int *NodoAnterior;
    Visitado = DaMemoriaArreglo(n);
    Valor = DaMemoriaArreglo(n);
    NodoAnterior = DaMemoriaArreglo(n);

    Visitado[inicial_nodo] = TRUE;
    for(i=0;i<n;i++)
    {
        if (Grafo[inicial_nodo][i] == 0)
            Valor[i] = inf;
        else
            Valor[i] = Grafo[inicial_nodo][i];
        NodoAnterior[i] = inicial_nodo;
    }
    while (NumeroNodosSinVisitar(Visitado, n)>1)
    {
        w = NodoMinimoCostoSinVisitar(Visitado, Valor, n);
        Visitado[w] = TRUE;
        for(j=0;j<n;j++)
        {
            if ((Grafo[w][j] != 0) && (!Visitado[j]))
            {
                if (Valor[w] + Grafo[w][j] < Valor[j])
                {
                    NodoAnterior[j] = w;
                    Valor[j] = Valor[w] + Grafo[w][j];
                }
            }
        }
    }
    /*Calcula el camino casi mas corto si existe de lo contrario entrega un -1*/
      if(p==1)
    {
        valor_minimo = Valor[final_nodo];
         if(valor_minimo == inf)
        {
            printf("\n-1\n");
        }
        p++;
    }


    if(p!=1&&valor_minimo==Valor[final_nodo])
    {
        if(valor_minimo == Valor[final_nodo])
        {
            Grafo[NodoAnterior[final_nodo]][final_nodo] = 0;
            DIJKSTRA(Grafo, n, inicial_nodo);
        }
    }
    else
    {
        ImprimeCaminos(NodoAnterior, Valor, n, inicial_nodo,final_nodo);
    }
}
/*Función que se ejecuta primero*/
int main()
{
    leer_archivo();
   InicializaVisitados();
            DIJKSTRA(Grafo, n, inicial_nodo);
            printf("\n");
   return 0;
}

