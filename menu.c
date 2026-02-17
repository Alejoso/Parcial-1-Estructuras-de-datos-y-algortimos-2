#include <stdio.h>

int leer_entero(int* valor) {
    if (scanf("%d", valor) != 1) {
        // Limpiar buffer de entrada en caso de error
        while (getchar() != '\n');
        return 0;
    }
    return 1;
}