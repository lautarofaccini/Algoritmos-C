#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int anio;
    int mes;
    int dia;
} Fecha;

typedef struct Nodo
{
    char nombre[50];
    float consumo;
    Fecha fecha;
    int n_mesa;
    struct Nodo *prox;
} Nodo;

// Devuelve la fecha actual
Fecha fechaActual()
{
    Fecha f;
    time_t t = time(NULL);
    struct tm *hoy = localtime(&t);
    f.anio = (*hoy).tm_year + 1900;
    f.mes = (*hoy).tm_mon + 1;
    f.dia = (*hoy).tm_mday;
    return f;
}

// Busca un cliente y devuelve su puntero; si se pasa 'ant', guarda el anterior
Nodo *buscarCliente(Nodo *prim, char nombre[], Nodo **ant)
{
    Nodo *p = prim;
    *ant = NULL;
    while (p != NULL && strcmp((*p).nombre, nombre) != 0)
    {
        *ant = p;
        p = (*p).prox;
    }
    return p;
}

// Mostrar toda la lista
void mostrarLista(Nodo *prim)
{
    Nodo *p = prim;
    if (p == NULL)
    {
        printf("No hay clientes en la lista.\n");
        return;
    }

    printf("\n=== LISTA DE CLIENTES ===\n");
    while (p != NULL)
    {
        printf("%s | Mesa %d | $%.2f | %02d/%02d/%04d\n",
               (*p).nombre, (*p).n_mesa, (*p).consumo,
               (*p).fecha.dia, (*p).fecha.mes, (*p).fecha.anio);
        p = (*p).prox;
    }
    printf("==========================\n");
}

// Liberar toda la memoria antes de salir
void liberarLista(Nodo **prim)
{
    Nodo *p;
    while (*prim != NULL)
    {
        p = *prim;
        *prim = (*prim)->prox;
        free(p);
    }
}

int main()
{
    Nodo *Prim = NULL, *ant = NULL, *p;
    int op, opc;
    char nombre[50];
    int n_mesa;

    printf("Desea empezar con la jornada? 1. Si, 2. No: ");
    scanf("%d", &op);

    while (op == 1)
    {
        printf("\nQue desea hacer?\n");
        printf("1. Cargar Cliente\n2. Registrar Consumo\n3. Realizar Cobro\n4. Eliminar Cliente\n");
        scanf("%d", &opc);

        printf("Ingrese el nombre del cliente: ");
        scanf(" %[^\n]", nombre); // permite espacios

        switch (opc)
        {
        case 1:
            printf("Ingrese el numero de mesa: ");
            scanf("%d", &n_mesa);
            // Crear Nodo
            Nodo *q = (Nodo *)malloc(sizeof(Nodo)); // Nuevo (q)
            if (q == NULL)
            {
                printf("Error: no se pudo asignar memoria.\n");
                exit(1);
            }
            strcpy((*q).nombre, nombre); // No se puede asignar directamente
            (*q).consumo = 0;
            (*q).fecha = fechaActual();
            (*q).n_mesa = n_mesa;
            (*q).prox = NULL;

            p = Prim;

            // Buscar la posición correcta
            while (p != NULL && strcmp((*p).nombre, (*q).nombre) < 0) // *p.nombre < *q.nombre
            {
                ant = p;
                p = (*p).prox;
            }

            // Insertar al inicio
            if (ant == NULL)
            {
                (*q).prox = Prim;
                Prim = q;
            }
            else // Insertar en el medio o final
            {
                (*ant).prox = q;
                (*q).prox = p;
            }
            break;
        case 2:
            p = buscarCliente(Prim, nombre, &ant);
            if (p == NULL)
            {
                printf("Cliente no encontrado.\n");
                break;
            }

            float consumo;
            printf("Ingrese el q consumo: ");
            scanf("%f", &consumo);
            (*p).consumo += consumo;
            printf("Consumo actualizado correctamente.\n");
            break;
        case 3:
            p = buscarCliente(Prim, nombre, &ant);
            if (p == NULL)
            {
                printf("Cliente no encontrado.\n");
                break;
            }
            printf("\n--- TICKET ---\n");
            printf("Nombre: %s\n", (*p).nombre);
            printf("Fecha: %02d/%02d/%04d\n", (*p).fecha.dia, (*p).fecha.mes, (*p).fecha.anio);
            printf("Mesa: %d\n", (*p).n_mesa);
            printf("Total: $%.2f\n", (*p).consumo);
            printf("----------------\n");
            break;
        case 4:
            p = buscarCliente(Prim, nombre, &ant);
            if (p == NULL)
            {
                printf("Cliente no encontrado.\n");
                break;
            }
            if (p == Prim)
                Prim = (*p).prox; // era el primero
            else
                (*ant).prox = (*p).prox;

            free(p);
            printf("Cliente eliminado correctamente.\n");
            break;
        default:
            printf("Opcion invalida.\n");
        }

        printf("\nDesea continuar? 1. Si, 2. No: ");
        scanf("%d", &op);
    }

    // Mostrar lista final y liberar memoria
    mostrarLista(Prim);
    liberarLista(&Prim);

    printf("Fin del programa.\n");
    return 0;
}