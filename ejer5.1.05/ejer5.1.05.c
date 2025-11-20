#include <stdio.h>
#include <stdbool.h>

bool Pares(int N) {
    if (N > 10) {
        if ((N % 10) % 2 == 0) {
            return Pares(N / 10);
        } else {
            return false;
        }
    } else {
        return (N % 2 == 0);
    }
}

int main() {
    int n;
    printf("Ingrese un numero: ");
    scanf("%d", &n);

    if (Pares(n))
        printf("Todos los dígitos son pares\n");
    else
        printf("Hay digitos impares\n");
    return 0;
}
