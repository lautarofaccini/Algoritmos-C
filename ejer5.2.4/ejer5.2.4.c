#include <stdio.h>

void Binario(int x) {
    if (x / 2 == 0) {     // división entera
        printf("1");
    } else {
        Binario(x / 2);   // división entera
        printf("%d", x % 2);
    }
}

int main() {
    int x;

    printf("Escribe un numero: ");
    scanf("%d", &x);

    printf("El numero binario es: ");
    Binario(x);

    return 0;
}
