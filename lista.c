#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

// Crea una nueva lista vacía inicializando sus punteros y tamaño
// Retorna un puntero a la estructura Lista creada o NULL en caso de error
Lista* crear_lista(void) {
    Lista* nueva = (Lista*)malloc(sizeof(Lista));
    if (!nueva) {
        fprintf(stderr, "Error: No se pudo asignar memoria para Lista\n");
        return NULL;
    }
    
    nueva->cabeza = NULL;
    nueva->tamanio = 0;
    return nueva;
}

// Libera toda la memoria asociada a la lista, incluyendo sus nodos y el contenido de las personas
// Recibe un puntero a la lista a destruir
void destruir_lista(Lista* lista) {
    if (!lista) {
        fprintf(stderr, "Advertencia: Intento de destruir lista NULL\n");
        return;
    }
    
    Nodo* actual = lista->cabeza;
    while (actual) {
        Nodo* siguiente = actual->siguiente;
        liberarvehiculo(actual->vehiculo);
        free(actual);
        actual = siguiente;
    }
    
    free(lista);
}

// Inserta una persona nueva al final de la lista
// Retorna 1 si la inserción fue exitosa, 0 en caso contrario
int insertar_al_final(Lista* lista, Vehiculo* vehiculo) {
    if (!lista) {
        fprintf(stderr, "Error: Lista NULL en insertar_al_final\n");
        return 0;
    }
    
    if (!vehiculo) {
        fprintf(stderr, "Error: Persona NULL en insertar_al_final\n");
        return 0;
    }
    
    Nodo* nuevo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (!nuevo_nodo) {
        fprintf(stderr, "Error: No se pudo asignar memoria para Nodo\n");
        return 0;
    }
    
    nuevo_nodo->vehiculo = vehiculo;
    nuevo_nodo->siguiente = NULL;
    
    if (lista->cabeza == NULL) {
        lista->cabeza = nuevo_nodo;
    } else {
        Nodo* actual = lista->cabeza;
        while (actual->siguiente) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo_nodo;
    }
    
    lista->tamanio++;
    return 1;
}

// Imprime el contenido de la lista en la consola
// Muestra una lista numerada de las personas almacenadas
void imprimir_lista(const Lista* lista) {
    if (!lista) {
        printf("Lista: NULL\n");
        return;
    }
    
    if (lista->tamanio == 0) {
        printf("Lista vacía (0 elementos)\n");
        return;
    }
    
    printf("Lista (%d elementos):\n", lista->tamanio);
    printf("=================================================================================\n");
    
    Nodo* actual = lista->cabeza;
    int i = 1;
    while (actual) {
        printf("%3d. ", i++);
        imprimirVehiculo(actual->vehiculo);
        actual = actual->siguiente;
    }
    printf("=================================================================================\n");
}

// Crea una copia profunda de la lista original
// Retorna una nueva lista que contiene copias de todas las personas de la lista original
Lista* copiar_lista(const Lista* original) {
    if (!original) {
        fprintf(stderr, "Error: Lista original NULL en copiar_lista\n");
        return NULL;
    }
    
    Lista* copia = crear_lista();
    if (!copia) {
        fprintf(stderr, "Error: No se pudo crear lista copia\n");
        return NULL;
    }
    
    Nodo* actual = original->cabeza;
    while (actual) {
        if (!actual->vehiculo) {
            fprintf(stderr, "Advertencia: Persona NULL encontrada en lista original\n");
            actual = actual->siguiente;
            continue;
        }
        
        Vehiculo* vehiculoCopia = crearVehiculo(
            actual->vehiculo->placa,
            actual->vehiculo->tipo,
            actual->vehiculo->sentido,
            actual->vehiculo->horaMilitar,
            actual->vehiculo->dia,
            actual->vehiculo->tiempoTramo,
            actual->vehiculo->estacion
        );
        
        if (vehiculoCopia) {
            if (!insertar_al_final(copia, vehiculoCopia)) {
                liberarvehiculo(vehiculoCopia);
                fprintf(stderr, "Error: No se pudo insertar persona en copia\n");
            }
        } else {
            fprintf(stderr, "Error: No se pudo crear copia de persona\n");
        }
        
        actual = actual->siguiente;
    }
    
    return copia;
}

// Verifica si la lista está vacía o es NULL
// Retorna 1 si está vacía, 0 si tiene elementos
int esta_vacia_lista(const Lista* lista) {
    return !lista || lista->tamanio == 0;
}