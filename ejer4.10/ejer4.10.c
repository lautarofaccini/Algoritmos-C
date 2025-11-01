#include <stdio.h>
#include <stdlib.h>

// Definición de la lista circular simple
typedef struct Nodo1
{
    int num;
    struct Nodo1 *prox;
} Nodo1;

// Definición de la lista doblemente enlazada
typedef struct Nodo2
{
    float num;
    struct Nodo2 *prox;
    struct Nodo2 *ant;
} Nodo2;

// Función principal que simula el proceso del pseudocódigo
void Ejer4_10(Nodo1 *Prim1)
{
    if (Prim1 == NULL)
    {
        printf("Error: lista circular vacía\n");
        return;
    }

    Nodo1 *p = Prim1;
    Nodo2 *Prim2 = NULL;
    Nodo2 *Ult2 = NULL;

    do
    {                     // Repetir
        int a = (*p).num; // cantidad de elementos del grupo
        p = (*p).prox;

        int acum = 0;
        for (int i = 0; i < a; i++)
        {
            acum = acum + (*p).num;
            p = (*p).prox;
        }

        float prom = (float)acum / a;
        Nodo2 *q = (Nodo2 *)malloc(sizeof(Nodo2));
        if (q == NULL)
        {
            printf("Error: sin memoria disponible\n");
            exit(1);
        }
        (*q).num = prom;
        (*q).prox = NULL;
        (*q).ant = NULL;

        // Caso 1: lista vacía
        if (Prim2 == NULL)
        {
            Prim2 = q;
            Ult2 = q;
        }
        else
        {
            Nodo2 *r = Prim2;

            // Buscar posición ordenada ascendente
            while (r != NULL && (*r).num <= (*q).num)
                r = (*r).prox;

            // Caso 2: insertar al final
            if (r == NULL)
            {
                Ult2 = q;
                (*q).ant = Ult2;
                (*Ult2).prox = q;
            }
            // Caso 3: insertar al inicio
            else if (r == Prim2)
            {
                Prim2 = q;
                (*q).prox = r;
                (*r).ant = q;
            }
            // Caso 4: insertar en el medio
            else
            {
                (*(*r).ant).prox = q;
                (*q).ant = (*r).ant;
                (*q).prox = r;
                (*r).ant = q;
            }
        };
    } while (p != Prim1); // recorrer lista circular completa

    // Mostrar lista circular
    printf("Lista circular:\n");
    Nodo1 *temp1 = Prim1;
    do
    {
        printf("%d -> ", temp1->num);
        temp1 = temp1->prox;
    } while (temp1 != Prim1);
    printf("(vuelve al inicio)\n\n");

    // Mostrar lista de promedios
    printf("Lista de promedios:\n");
    Nodo2 *temp2 = Prim2;
    while (temp2 != NULL)
    {
        printf("%.2f -> ", temp2->num);
        temp2 = temp2->prox;
    }
    printf("NULL\n\n");

    // Mostrar resultados
    if (Prim2 != NULL && Ult2 != NULL)
    {
        printf("Promedio mínimo: %.2f\n", (*Prim2).num);
        printf("Promedio máximo: %.2f\n", (*Ult2).num);
    }
    else
    {
        printf("No se generó la lista de promedios.\n");
    }
}

// Función auxiliar para crear una lista circular de ejemplo
Nodo1 *crearListaCircularEjemplo()
{
    // Ejemplo con 6 grupos, cada uno comienza con la cantidad de elementos que siguen
    // Por ejemplo: [3, 10, 20, 30, 2, 5, 15, 1, 7, ...]
    int datos[] = {3, 10, 20, 30, 2, 5, 15, 1, 7, 4, 12, 14, 16, 2};
    int n = sizeof(datos) / sizeof(datos[0]);

    Nodo1 *Prim = NULL;
    Nodo1 *Ult = NULL;

    for (int i = 0; i < n; i++)
    {
        Nodo1 *nuevo = (Nodo1 *)malloc(sizeof(Nodo1));
        (*nuevo).num = datos[i];
        (*nuevo).prox = NULL;

        if (Prim == NULL)
            Prim = nuevo;
        else
            (*Ult).prox = nuevo;

        Ult = nuevo;
    }

    // Cerrar la lista para hacerla circular
    (*Ult).prox = Prim;
    return Prim;
}

// Programa principal
int main()
{
    Nodo1 *listaCircular = crearListaCircularEjemplo();

    Ejer4_10(listaCircular);

    return 0;
}
