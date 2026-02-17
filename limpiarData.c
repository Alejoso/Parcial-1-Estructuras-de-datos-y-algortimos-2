#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <math.h>

#include "lista.h"
#include "generador.h"

// Devuelve 1 si est está en la lista "prohibida"
static int estacion_prohibida(const char* est) {
    if (!est) return 0;

    static const char* prohibidas[] = {
        "Exposiciones",
        "Alpujarra",
        "San Antonio",
        "Parque Berrío",
        "Prado",
        "Hospital",
        "Universidad"
    };

    for (size_t i = 0; i < sizeof(prohibidas)/sizeof(prohibidas[0]); i++) {
        if (strcmp(est, prohibidas[i]) == 0) return 1;
    }
    return 0;
}

// Valida hhmm y rango 05:00..20:00
static int cumple_horario(DiaSemana dia, int hhmm) {
    int hh = hhmm / 100;
    int mm = hhmm % 100;

    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) return 0; // hora inválida
    if (dia < LUNES || dia > VIERNES) return 0; // solo Lunes a viernes
    if (hhmm < 500 || hhmm > 2000) return 0; // solo 05:00 a 20:00

    return 1;
}

void limpiarLista(Lista* lista) {
    if (!lista) return;

    Nodo* actual = lista->cabeza;
    Nodo* anterior = NULL;

    while (actual) {
        Vehiculo* v = actual->vehiculo;
        int borrar = 0;
        if (!v) {
            borrar = 1;
        } else {
            if (!cumple_horario(v->dia, v->horaMilitar) || estacion_prohibida(v->estacion)) {
                borrar = 1;
            }
        }

        if (borrar) {
            Nodo* tmp = actual;
            actual = actual->siguiente;

            if (anterior) anterior->siguiente = actual;
            else lista->cabeza = actual;

            if (tmp->vehiculo) free(tmp->vehiculo); 
            free(tmp);

            if (lista->tamanio > 0) lista->tamanio--;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

static int cmp_float_desc(const void* p1, const void* p2) {
    float a = *(const float*)p1;
    float b = *(const float*)p2;
    if (a < b) return 1;
    if (a > b) return -1;
    return 0;
}

void limpiarLista20MasLentos(Lista* lista) {
    if (!lista || !lista->cabeza) return;

    int n = lista->tamanio;
    if (n <= 0) return;

    int k = (int)floor(0.20 * n);   // cantidad a eliminar
    if (k <= 0) return;

    // 1) Copiar tiempos a un arreglo
    float* tiempos = (float*)malloc(sizeof(float) * n);
    if (!tiempos) return;

    int idx = 0;
    for (Nodo* t = lista->cabeza; t && idx < n; t = t->siguiente) {
        // si por alguna razón vehiculo es NULL, lo tratamos como muy lento
        tiempos[idx++] = (t->vehiculo) ? t->vehiculo->tiempoTramo : INFINITY;
    }

    // 2) Ordenar desc y obtener umbral del k-ésimo más lento
    qsort(tiempos, idx, sizeof(float), cmp_float_desc);
    if (k > idx) k = idx;
    float umbral = tiempos[k - 1];
    free(tiempos);

    int removidos = 0;

    // 3) Primera pasada: borrar todos los que sean > umbral
    Nodo* actual = lista->cabeza;
    Nodo* anterior = NULL;

    while (actual && removidos < k) {
        float tt = actual->vehiculo ? actual->vehiculo->tiempoTramo : INFINITY;

        if (tt > umbral) {
            Nodo* borrar = actual;
            actual = actual->siguiente;

            if (anterior) anterior->siguiente = actual;
            else lista->cabeza = actual;

            liberarvehiculo(borrar->vehiculo);
            free(borrar);
            removidos++;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    // 4) Segunda pasada: si aún faltan, borrar los == umbral hasta completar k
    actual = lista->cabeza;
    anterior = NULL;

    while (actual && removidos < k) {
        float tt = actual->vehiculo ? actual->vehiculo->tiempoTramo : INFINITY;

        if (fabsf(tt - umbral) < 1e-6f) {
            Nodo* borrar = actual;
            actual = actual->siguiente;

            if (anterior) anterior->siguiente = actual;
            else lista->cabeza = actual;

            liberarvehiculo(borrar->vehiculo);
            free(borrar);
            removidos++;
        } else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    // 5) Actualizar tamaño
    lista->tamanio -= removidos;
}
