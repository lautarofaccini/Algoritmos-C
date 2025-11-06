#include <stdio.h>
#include <stdlib.h>

// Nodo simple
typedef struct Nodo
{
    int dato;
    struct Nodo *prox;
} Nodo;

// Procedimiento Ejer4_2 (versión sin malloc/free)
Nodo *Ejer4_2(Nodo **Prim1)
{
    Nodo *Prim2 = NULL; // nueva lista
    Nodo *q = NULL;

    Nodo *p = *Prim1;
    Nodo *ant = NULL;

    while (p != NULL)
    {
        if ((*p).dato % 10 == 0)
        {
            // Desenganchar nodo de lista original
            Nodo *v = p;
            if (ant == NULL)
            {
                // si es el primero
                *Prim1 = (*p).prox;
            }
            else
            {
                ant->prox = (*p).prox;
            }

            p = (*p).prox; // avanzar puntero antes de reconectar

            // Insertar en la nueva lista
            v->prox = NULL;
            if (Prim2 == NULL)
            {
                Prim2 = v;
                q = v;
            }
            else
            {
                (*q).prox = v;
                q = v;
            }
        }
        else
        {
            // avanzar en la lista original
            ant = p;
            p = (*p).prox;
        }
    }

    // Mostrar lista de múltiplos de 10
    printf("\nLista de múltiplos de 10 (Prim2):\n");
    Nodo *t = Prim2;
    while (t != NULL)
    {
        printf("%d -> ", t->dato);
        t = t->prox;
    }
    printf("NULL\n");

    // Devolvemos la cabeza de la nueva lista (Prim2)
    return Prim2;
}

int main()
{
    // Crear lista original: 10 -> 7 -> 20 -> 100 -> 3 -> NULL
    Nodo *Prim1 = malloc(sizeof(Nodo));
    Nodo *n2 = malloc(sizeof(Nodo));
    Nodo *n3 = malloc(sizeof(Nodo));
    Nodo *n4 = malloc(sizeof(Nodo));
    Nodo *n5 = malloc(sizeof(Nodo));

    Prim1->dato = 10;
    Prim1->prox = n2;
    n2->dato = 7;
    n2->prox = n3;
    n3->dato = 20;
    n3->prox = n4;
    n4->dato = 100;
    n4->prox = n5;
    n5->dato = 3;
    n5->prox = NULL;

    printf("Lista original:\n");
    Nodo *t = Prim1;
    while (t != NULL)
    {
        printf("%d -> ", t->dato);
        t = t->prox;
    }
    printf("NULL\n");

    Nodo *Prim2 = Ejer4_2(&Prim1);

    printf("\nLista final sin múltiplos de 10 (Prim1):\n");
    t = Prim1;
    while (t != NULL)
    {
        printf("%d -> ", t->dato);
        t = t->prox;
    }
    printf("NULL\n");

    // Liberar memoria
    Nodo *aux;
    while (Prim1 != NULL)
    {
        aux = Prim1;
        Prim1 = Prim1->prox;
        free(aux);
    }
    while (Prim2 != NULL)
    {
        aux = Prim2;
        Prim2 = Prim2->prox;
        free(aux);
    }

    return 0;
}
