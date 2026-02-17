#include <string.h>
#include <stdlib.h>

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