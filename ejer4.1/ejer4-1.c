#include <stdio.h>
#include <stdlib.h> // Necesaria para malloc() y free()

// Definición del tipo Nodo
typedef struct Nodo {
    int dato;
    struct Nodo* prox;
} Nodo;

// Procedimiento para mostrar error
void ERROR(const char* mensaje) {
    printf("Error: %s\n", mensaje);
}

// Función que implementa la acción 4.1
Nodo* Ejer4_1(Nodo* Prim) {
    Nodo *p, *q, *a;
    int k, opc;

    // Verificamos si la lista está vacía
    if (Prim != NULL) {
        p = Prim;
        a = NULL;

        printf("Ingrese una posición para operar: ");
        scanf("%d", &k);

        // Avanza hasta el k-ésimo nodo o hasta que la lista termine
        while (p != NULL && k > 1) {
            a = p;
            p = (*p).prox; // Se puede abreviar como p = p->prox;
            k = k - 1;
        }

        // Si p no es NULL, significa que la posición es válida
        if (p != NULL) {
            printf("Ingrese la opción deseada:\n");
            printf("1. Acceder\n2. Eliminar\n3. Insertar\n");
            scanf("%d", &opc);

            switch (opc) {
                case 1:
                    // Acceder al nodo p
                    printf("El elemento en la posición es: %d\n", (*p).dato);
                    break;

                case 2:
                    // Eliminar el nodo p
                    if (p != Prim) {
                        (*a).prox = (*p).prox;
                    } else {
                        Prim = (*p).prox;
                    }
                    free(p); // Disponer(q)
                    printf("El elemento ha sido eliminado.\n");
                    break;

                case 3:
                    // Insertar nuevo nodo antes de p
                    q = (Nodo*)malloc(sizeof(Nodo)); // Nuevo(q)
                    if (q == NULL) {
                        ERROR("No hay memoria suficiente");
                        return Prim;
                    }

                    printf("Ingrese el número a insertar: ");
                    scanf("%d", &(*q).dato);
                    (*q).prox = p;

                    if (p == Prim) {
                        Prim = q;
                    } else {
                        (*a).prox = q;
                    }

                    printf("El número %d se ha insertado en la posición.\n", (*q).dato);
                    break;

                default:
                    ERROR("Opción no válida");
                    break;
            }
        } else {
            ERROR("Elemento fuera de rango");
        }
    } else {
        ERROR("Lista vacía");
    }
    return Prim;
}

int main() {
    // Crear una lista de ejemplo: 10 -> 20 -> 30
    Nodo *Prim = malloc(sizeof(Nodo));
    if (Prim == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return 1;
    }

    Prim->dato = 10;
    Prim->prox = malloc(sizeof(Nodo));
    if (Prim->prox == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        free(Prim);
        return 1;
    }

    Prim->prox->dato = 20;
    Prim->prox->prox = malloc(sizeof(Nodo));
    if (Prim->prox->prox == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        free(Prim->prox);
        free(Prim);
        return 1;
    }

    Prim->prox->prox->dato = 30;
    Prim->prox->prox->prox = NULL;

    // Mostrar lista inicial
    printf("Lista inicial:\n");
    Nodo* temp = Prim;
    while (temp != NULL) {
        printf("%d -> ", temp->dato);
        temp = temp->prox;
    }
    printf("NULL\n\n");

    // Llamar a la acción 4.1 (devuelve la lista actualizada)
    Prim = Ejer4_1(Prim);

    // Mostrar lista final
    printf("\nLista final:\n");
    temp = Prim;
    while (temp != NULL) {
        printf("%d -> ", temp->dato);
        temp = temp->prox;
    }
    printf("NULL\n");

    // Liberar memoria antes de salir
    while (Prim != NULL) {
        Nodo* aux = Prim;
        Prim = Prim->prox;
        free(aux);
    }

    return 0;
}
