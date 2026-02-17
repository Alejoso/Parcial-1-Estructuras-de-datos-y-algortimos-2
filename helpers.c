#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "helpers.h"

void mostrarPrimerosVehiculos(const Lista* lista, int n, const char* titulo) {
    if (!lista) return;

    printf("\n=== %s ===\n", titulo);

    Nodo* actual = lista->cabeza;
    for (int i = 0; i < n && actual; i++) {
        printf("%d. ", i + 1);
        imprimirVehiculo(actual->vehiculo);   // <-- ajusta según cómo guardes el vehículo
        actual = actual->siguiente;
    }

    if (lista->tamanio > n) {
        printf("... (mostrando %d de %d)\n", n, lista->tamanio);
    }
}

double medir_tiempo_ordenacion(Lista* lista, 
                              void (*funcion)(Lista*), 
                              const char* nombre) {
    clock_t inicio, fin;
    
    printf("Ejecutando %s... ", nombre);
    fflush(stdout);
    
    inicio = clock();
    funcion(lista);
    fin = clock();
    
    double tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Completado en %.6f segundos\n", tiempo);
    
    return tiempo;
}

// Compara dos listas para verificar si contienen los mismos datos y en el mismo orden
int listas_son_iguales(const Lista* a, const Lista* b) {
    if (!a || !b) return 0;
    if (a->tamanio != b->tamanio) return 0;
    
    Nodo* nodo_a = a->cabeza;
    Nodo* nodo_b = b->cabeza;
    
    while (nodo_a && nodo_b) {
        if (!nodo_a->vehiculo || !nodo_b->vehiculo) return 0;
        
        if (strcmp(nodo_a->vehiculo->placa, nodo_b->vehiculo->placa) != 0 ||
            strcmp(nodo_a->vehiculo->estacion, nodo_b->vehiculo->estacion) != 0 ||
            nodo_a->vehiculo->tipo != nodo_b->vehiculo->tipo ||
            nodo_a->vehiculo->sentido != nodo_b->vehiculo->sentido ||
            nodo_a->vehiculo->horaMilitar != nodo_b->vehiculo->horaMilitar ||
            nodo_a->vehiculo->dia != nodo_b->vehiculo->dia ||
            nodo_a->vehiculo->tiempoTramo != nodo_b->vehiculo->tiempoTramo) {
            return 0;
        }
        nodo_a = nodo_a->siguiente;
        nodo_b = nodo_b->siguiente;
    }
    
    return 1;
}