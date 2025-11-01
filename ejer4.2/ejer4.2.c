#include <stdio.h>
#include <stdlib.h>

// Definición del nodo (equivalente al "registro" del pseudocódigo)
typedef struct Nodo
{
    int dato;
    struct Nodo *prox;
} Nodo;

// Procedimiento principal (Ejercicio 4.2)
Nodo *Ejer4_2(Nodo *Prim1)
{
    Nodo *p, *ant1, *q, *Prim2, *ant2;

    // Inicializamos la nueva lista vacía
    Prim2 = NULL;
    ant2 = NULL;
    ant1 = NULL;
    // Proceso principal
    if (Prim1 != NULL)
    {
        p = Prim1;
        while (p != NULL)
        {
            if ((*p).dato % 10 == 0)
            {
                q = (Nodo *)malloc(sizeof(Nodo)); // nuevo(q)
                if (q == NULL)
                {
                    printf("Error: no hay memoria disponible.\n");
                    exit(1);
                }

                (*q).dato = (*p).dato; // *q.dato := *p.dato
                (*q).prox = NULL;      // *q.prox := NIL

                if (Prim2 == NULL)
                {
                    Prim2 = q; // si Prim2 está vacía, este es el primer nodo
                }
                else
                {
                    (*ant2).prox = q; // si no, lo encadenamos al final
                }
                ant2 = q; // ant2 apunta al último nodo insertado
                if (p == Prim1)
                {
                    // Si es el primer nodo
                    Prim1 = (*p).prox; // avanzar inicio
                    free(p);           // liberar nodo
                    p = Prim1;         // mover puntero p
                }
                else
                {
                    (*ant1).prox = (*p).prox; // saltar el nodo p
                    free(p);
                    p = (*ant1).prox; // continuar desde el siguiente
                } // eliminar de lista original
            }
            else
            {
                ant1 = p;
                p = (*p).prox;
            }
        }
    }
    // Mostrar la nueva lista con los múltiplos de 10
    printf("\nLista de múltiplos de 10 (Prim2):\n");
    Nodo *temp = Prim2;
    while (temp != NULL)
    {
        printf("%d -> ", (*temp).dato);
        temp = (*temp).prox;
    }
    printf("NULL\n");

    // Devolvemos la lista original (ya sin múltiplos de 10)
    return Prim1;
}

int main()
{
    // Crear lista original: 9 -> 7 -> 6 -> 4 -> 3 -> NULL
    Nodo *Prim1 = malloc(sizeof(Nodo));
    Prim1->dato = 10;
    Prim1->prox = malloc(sizeof(Nodo));
    Prim1->prox->dato = 7;
    Prim1->prox->prox = malloc(sizeof(Nodo));
    Prim1->prox->prox->dato = 20;
    Prim1->prox->prox->prox = malloc(sizeof(Nodo));
    Prim1->prox->prox->prox->dato = 100;
    Prim1->prox->prox->prox->prox = malloc(sizeof(Nodo));
    Prim1->prox->prox->prox->prox->dato = 3;
    Prim1->prox->prox->prox->prox->prox = NULL;

    printf("Lista original:\n");
    Nodo *t = Prim1;
    while (t != NULL)
    {
        printf("%d -> ", t->dato);
        t = t->prox;
    }
    printf("NULL\n");

    // Llamamos ant1 la acción 4.2
    Prim1 = Ejer4_2(Prim1);

    // Mostrar lista final (ya sin múltiplos de 10)
    printf("\nLista final sin múltiplos de 10:\n");
    t = Prim1;
    while (t != NULL)
    {
        printf("%d -> ", t->dato);
        t = t->prox;
    }
    printf("NULL\n");

    // Liberar memoria al final
    while (Prim1 != NULL)
    {
        Nodo *aux = Prim1;
        Prim1 = Prim1->prox;
        free(aux);
    }

    return 0;
}
