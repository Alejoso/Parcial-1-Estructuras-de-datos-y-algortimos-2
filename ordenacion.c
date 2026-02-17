#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacion.h"

int comparar_personas(const Vehiculo* a, const Vehiculo* b) {
    if (!a || !b) return 0;

    int rankA, rankB;

    switch (a->tipo) {
        case EMERGENCIA:
            rankA = 0; break;
        case MEDICO:
            rankA = 1; break;
        case PASAJEROS:
            rankA = 2; break;
        case CARGA:
            rankA = 3; break;
        case TAXI: 
            rankA = 4; break;
        default:
            rankA = 5; break;
    }

    switch (b->tipo) {
        case EMERGENCIA:
            rankB = 0; break;
        case MEDICO:
            rankB = 1; break;
        case PASAJEROS:
            rankB = 2; break;
        case CARGA:
            rankB = 3; break;
        case TAXI: 
            rankB = 4; break;
        default:
            rankB = 5; break;
    }

    if (rankA < rankB) return -1;
    if (rankA > rankB) return  1;

    if (a->tiempoTramo > b->tiempoTramo) return -1;
    if (a->tiempoTramo < b->tiempoTramo) return  1;

    return 0;
}

static void intercambiar_nodos(Nodo* a, Nodo* b) {
    Vehiculo* temp = a->vehiculo;
    a->vehiculo = b->vehiculo;
    b->vehiculo = temp;
}

static Nodo* fusionar(Nodo* a, Nodo* b) {
    if (!a) return b;
    if (!b) return a;
    
    if (comparar_personas(a->vehiculo, b->vehiculo) <= 0) {
        a->siguiente = fusionar(a->siguiente, b);
        return a;
    } else {
        b->siguiente = fusionar(a, b->siguiente);
        return b;
    }
}

static void dividir_lista(Nodo* cabeza, Nodo** mitad) {
    Nodo* rapido = cabeza->siguiente;
    Nodo* lento = cabeza;
    
    while (rapido) {
        rapido = rapido->siguiente;
        if (rapido) {
            rapido = rapido->siguiente;
            lento = lento->siguiente;
        }
    }
    
    *mitad = lento->siguiente;
    lento->siguiente = NULL;
}

static Nodo* mergesort_recursivo(Nodo* cabeza) {
    if (!cabeza || !cabeza->siguiente) {
        return cabeza;
    }
    
    Nodo* mitad = NULL;
    dividir_lista(cabeza, &mitad);
    
    cabeza = mergesort_recursivo(cabeza);
    mitad = mergesort_recursivo(mitad);
    
    return fusionar(cabeza, mitad);
}

void ordenar_mergesort(Lista* lista) {
    if (!lista || lista->tamanio < 2) return;
    
    lista->cabeza = mergesort_recursivo(lista->cabeza);
}

static Nodo* particionar(Nodo* primero, Nodo* ultimo) {
    Nodo* pivote = primero;
    Nodo* frontera = primero;
    Nodo* actual = primero->siguiente;
    
    while (actual != ultimo->siguiente) {
        if (comparar_personas(actual->vehiculo, pivote->vehiculo) < 0) {
            frontera = frontera->siguiente;
            intercambiar_nodos(frontera, actual);
        }
        actual = actual->siguiente;
    }
    
    intercambiar_nodos(primero, frontera);
    return frontera;
}

static void quicksort_recursivo(Nodo* primero, Nodo* ultimo) {
    if (!primero || !ultimo || primero == ultimo || primero == ultimo->siguiente) {
        return;
    }
    
    Nodo* pivote = particionar(primero, ultimo);
    
    if (pivote != primero) {
        Nodo* temp = primero;
        while (temp->siguiente != pivote) {
            temp = temp->siguiente;
        }
        quicksort_recursivo(primero, temp);
    }
    
    if (pivote != ultimo) {
        quicksort_recursivo(pivote->siguiente, ultimo);
    }
}

void ordenar_quicksort(Lista* lista) {
    if (!lista || lista->tamanio < 2) return;
    
    Nodo* ultimo = lista->cabeza;
    while (ultimo->siguiente) {
        ultimo = ultimo->siguiente;
    }
    
    quicksort_recursivo(lista->cabeza, ultimo);
}