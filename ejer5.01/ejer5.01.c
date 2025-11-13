#include <stdio.h>

// Función recursiva que calcula el factorial de un número
double factorial(double n) {
    // Caso base
    if (n == 0) {
        printf("factorial(0) = 1\n");
        return 1;
    } 
    else {
        // Mostrar antes de la llamada recursiva
        printf("Calculando: %.0f * factorial(%.0f)\n", n, n - 1);

        double resultado = n * factorial(n - 1);

        // Mostrar después de obtener el resultado de la recursión
        printf("Resultado parcial: %.0f! = %.0f\n", n, resultado);

        return resultado;
    }
}

int main() {
    double n;

    printf("Ingrese el número para calcular su factorial: ");
    scanf("%lf", &n);

    if (n < 0) {
        printf("Error: el número debe ser positivo.\n");
        return 1;
    }

    printf("\n=== PROCESO RECURSIVO ===\n");
    double resultado = factorial(n);

    printf("\n=== RESULTADO FINAL ===\n");
    printf("El factorial de %.0f es: %.0f\n", n, resultado);

    return 0;
}
