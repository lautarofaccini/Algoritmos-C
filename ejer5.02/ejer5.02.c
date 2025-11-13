#include <stdio.h>

// Función recursiva que calcula el n-ésimo número de Fibonacci
int Fib(int n) {
    // Casos base
    if (n == 1 || n == 2) {
        return 1;
    } else {
        // Llamadas recursivas
        int resultado = Fib(n - 1) + Fib(n - 2);

        return resultado;
    }
}

int main() {
    int n;

    printf("Escriba un número para calcular Fibonacci: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: el número debe ser positivo.\n");
        return 1;
    }

    printf("\n=== PROCESO RECURSIVO ===\n");
    int resultado = Fib(n);

    printf("\n=== RESULTADO FINAL ===\n");
    printf("El término %d de la serie de Fibonacci es: %d\n", n, resultado);

    return 0;
}
