#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define inf 3000000

typedef int BOOL;

int n_nodos;
int n_aristas;
int nodo_inicial;
int nodo_final;
int **Matriz = NULL;
BOOL *Visitado = NULL;
int costo_min=0;
int c=1;

int *DaMemoriaArreglo(int n)
{
    int *aux, i;

    aux = (int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        aux[i] = FALSE;
    return aux;
}

void InicializaVisitados()
{
    int i;
    for(i=0;i<n_nodos;i++)
        Visitado[i] = FALSE;
}
void ImprimeCaminos(int **Grafo, int *NodoAnterior, int *Costo, int n, int v0)
{
    int *Camino, i, j, nodo;

    Camino = DaMemoriaArreglo(n);

    for(i=0;i<n;i++)
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

            if(Costo[i]!=inf)
            {
                if(i==nodo_final)
                {
                    printf("\n\t%2d -> %2d ($%3d): ", v0, i, Costo[i]);
                    while (j >= 0)
                    {
                        printf("%3d", Camino[j]);
                        j--;
                    }
                }
            }
            else
                exit(-1);
        }
    }
    printf("\n\n");
}

int NumeroNodosSinVisitar(int *Visitado, int n)
{
    int i, cont;

    i = 0;
    cont = 0;

    while (i < n)
    {
        if (!Visitado[i])
            cont++;
        i++;
    }
   return cont;
}

int NodoMinimoCostoSinVisitar(int *Visitado, int *Costo, int n)
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
void DIJKSTRA(int **Grafo, int n, int v0)
{
    BOOL *Visitado;
    int *Costo;
    int *NodoAnterior;
    int i, j, w = v0;

    Visitado = DaMemoriaArreglo(n);
    Costo = DaMemoriaArreglo(n);
    NodoAnterior = DaMemoriaArreglo(n);

    Visitado[v0] = TRUE;
    for(i=0;i<n;i++)
    {
        if (Grafo[v0][i] == 0)
            Costo[i] = inf;
        else
            Costo[i] = Grafo[v0][i];
        NodoAnterior[i] = v0;
    }
    while (NumeroNodosSinVisitar(Visitado, n)>1)
    {
        w = NodoMinimoCostoSinVisitar(Visitado, Costo, n);
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

    if(c==1)
    {
        costo_min = Costo[nodo_final];
        c++;
    }

    if(c!=1&&costo_min==Costo[nodo_final])
    {
        if(costo_min == Costo[nodo_final])
        {
            Grafo[NodoAnterior[nodo_final]][nodo_final] = 0;
            DIJKSTRA(Grafo, n, v0);
        }
    }
    else
    {
        ImprimeCaminos(Grafo, NodoAnterior, Costo, n, v0);
    }
}


void Lectura_Archivo()
{
    FILE *archivo;
    char n_archivo[100];
    int condicion = 0, m, n, i, j, x;

    while(condicion==0)
    {
        printf("Ingrese nombre del archivo: ");
        scanf("%s", n_archivo);
        archivo = fopen(n_archivo,"r");

        if(archivo!=NULL)
        {
            fscanf(archivo, "%d", &n_nodos);
            fscanf(archivo, "%d", &n_aristas);
            fscanf(archivo, "%d", &nodo_inicial);
            fscanf(archivo, "%d", &nodo_final);

            /*Casteo Matriz dinamica*/
            Matriz = (int **)malloc(n_nodos*sizeof(int));
            for(n=0; n<n_nodos; n++)
                Matriz[n] = (int *) malloc(n_nodos*sizeof(int));

            if(Matriz == NULL)
            {
                printf("NO hay suficiente espacio en memoria\n\n");
                condicion++;
            }

            /*Se llena la matriz con 0*/
            for(n=0; n<n_nodos;n++)
            {
                for(m=0; m<n_nodos;m++)
                    Matriz[n][m]=0;
            }

            /*Se cargan los datos del archivo a la matriz*/
            for(n=0; n<n_aristas; n++)
            {
                fscanf(archivo, "%d", &i);
                fscanf(archivo, "%d", &j);
                fscanf(archivo, "%d", &x);
                Matriz[i][j] = x;
            }
            Visitado = DaMemoriaArreglo(n_nodos);
            fclose(archivo);
        }
        else
        {
            printf("No se encontr%c el archivo.\n\n", 162);
            exit(0);
        }
        condicion++;
    }
    DIJKSTRA(Matriz, n_nodos, nodo_inicial);

    /*
    printf("\n");
    for(m=0; m<n_nodos; m++)
    {
        for(n=0; n<n_nodos; n++)
        {
            printf("%4d", Matriz[m][n]);
        }
        printf("\n");
    }/*

}

int main()
{
    Lectura_Archivo();
    return 0;
}
