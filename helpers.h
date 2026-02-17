#ifndef HELPERS_H
#define HELPERS_H
#include "lista.h"

// Mide el tiempo de ejecución de un algoritmo de ordenación
// Retorna el tiempo en segundos
// double medir_tiempo_ordenacion(Lista* lista, CriterioOrden criterio, 
//                               void (*funcion)(Lista*, CriterioOrden), 
//                               const char* nombre);

// Compara dos listas para verificar si contienen los mismos datos y en el mismo orden
// Retorna 1 si son iguales, 0 si son diferentes
int listas_son_iguales(const Lista* a, const Lista* b);

// Muestra las estadísticas de nombres y apellidos de la lista
void mostrar_estadisticas_lista(const Lista* lista);

// Muestra las primeras N personas de la lista
void mostrarPrimerosVehiculos(const Lista* lista, int n, const char* titulo);

double medir_tiempo_ordenacion(Lista* lista, 
                              void (*funcion)(Lista*), 
                              const char* nombre);

#endif