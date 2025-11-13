#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
    char nombre[30];
    char estado[2]; // "P" o "E"
    char direccion[50];
    long telefono;
    float total;
    struct Nodo* prox;
    struct Nodo* ant;
} Nodo;

Nodo *Prim, *Ult, *p, *q;
int opc1, opc2;
char nombre[30];

void mostrarLista() {
    Nodo* aux = Prim;
    printf("\n=== ESTADO ACTUAL DE LA LISTA ===\n");
    if (aux == NULL) {
        printf("Lista vacía.\n");
        return;
    }

    while (aux != NULL) {
        printf("Cliente: %-20s | Estado: %s | Total: $%.2f | Tel: %ld | Dir: %s\n",
               aux->nombre, aux->estado, aux->total, aux->telefono, aux->direccion);
        aux = aux->prox;
    }
    printf("=================================\n");
}

void registrarPedido() {
    q = (Nodo*)malloc(sizeof(Nodo));
    strcpy((*q).estado, "P");
    strcpy((*q).nombre, nombre);
    printf("Ingrese la dirección: ");
    scanf(" %[^\n]", (*q).direccion);
    printf("Ingrese el teléfono: ");
    scanf("%ld", &(*q).telefono);
    printf("Ingrese el monto: ");
    scanf("%f", &(*q).total);
    (*q).prox = NULL;
    (*q).ant = NULL;

    // Insertar ordenado por nombre
    p = Prim;
    while (p != NULL && strcmp((*p).nombre, (*q).nombre) < 0) {
        p = (*p).prox;
    }

    if (Prim == NULL) { // lista vacía
        Prim = q;
        Ult = q;
    } else if (p == Prim && strcmp((*p).nombre, (*q).nombre) > 0) { // insertar al principio
        (*q).prox = Prim;
        (*Prim).ant = q;
        Prim = q;
    } else if (p == NULL) { // insertar al final
        (*Ult).prox = q;
        (*q).ant = Ult;
        Ult = q;
    } else { // insertar en el medio
        (*q).prox = p;
        (*q).ant = (*p).ant;
        (*(*p).ant).prox = q;
        (*p).ant = q;
    }

    printf("\nPedido registrado correctamente.\n");
    mostrarLista();
}

void eliminarPedido() {
    if (strcmp((*p).estado, "P") == 0) {
        printf("No se puede realizar el cobro\n");
    } else {
        if (p == Prim && p == Ult) { // único elemento
            Prim = NULL;
            Ult = NULL;
        } else if (p == Prim) { // primero
            Prim = (*p).prox;
            (*Prim).ant = NULL;
        } else if (p == Ult) { // último
            Ult = (*p).ant;
            (*Ult).prox = NULL;
        } else { // en el medio
            (*(*p).ant).prox = (*p).prox;
            (*(*p).prox).ant = (*p).ant;
        }
        printf("Pedido de '%s' eliminado.\n", (*p).nombre);
        free(p);
    }
    mostrarLista();
}

int main() {
    Prim = NULL;
    Ult = NULL;

    printf("Quiere empezar a operar? 1. Si, 2. No\n");
    scanf("%d", &opc1);

    while (opc1 == 1) {
        p = Prim;
        printf("\nIngrese el nombre del cliente: ");
        scanf(" %[^\n]", nombre);

        while (p != NULL && strcmp((*p).nombre, nombre) != 0) {
            p = (*p).prox;
        }

        if (p != NULL && strcmp((*p).nombre, nombre) == 0) {
            printf("Elija una opción: 1. Enviar Pedido, 2. Eliminar Pedido\n");
            scanf("%d", &opc2);

            switch (opc2) {
                case 1:
                    strcpy((*p).estado, "E");
                    break;
                case 2:
                    eliminarPedido();
                    break;
                default:
                    printf("Error, elija una opción válida.\n");
                    break;
            }
        } else {
            registrarPedido();
        }

        printf("Quiere seguir operando? 1. Si, 2. No\n");
        scanf("%d", &opc1);
    }

    printf("\n=== ESTADO FINAL DE LA LISTA ===\n");
    mostrarLista();

    // Liberar memoria
    p = Prim;
    while (p != NULL) {
        q = p;
        p = (*p).prox;
        free(q);
    }

    printf("\nMemoria liberada. Fin del programa.\n");
    return 0;
}
