#include "generador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* estaciones[] = {
    "La Estrella",
    "Sabaneta",
    "Itagüí",
    "Envigado",
    "Ayurá",
    "Aguacatala",
    "Poblado",
    "Industriales",
    "Exposiciones",
    "Plaza Mayor",
    "San Antonio",
    "Parque Berrío",
    "Prado",
    "Hospital",
    "Universidad",
    "Tricentenario",
    "Caribe",
    "Acevedo",
    "Madera",
    "Bello",
    "Niquía"
};



Vehiculo* crearVehiculo(const char* placa , TipoVehiculo tipo , int sentido , int horaMilitar , DiaSemana dia , float tiempoTramo , const char* estacion)
{
    Vehiculo* vehiculo = (Vehiculo*)malloc(sizeof(Vehiculo));
    if (!vehiculo) {
        fprintf(stderr, "Error: No se pudo asignar memoria para un nuevo vehiculo\n");
        return NULL;
    }    

    strncpy(vehiculo->placa, placa, sizeof(vehiculo->placa) - 1);
    vehiculo->placa[sizeof(vehiculo->placa) - 1] = '\0';    vehiculo->tipo = tipo;
    vehiculo->sentido = sentido;
    vehiculo->horaMilitar = horaMilitar;
    vehiculo->dia = dia;
    vehiculo->tiempoTramo = tiempoTramo;
    vehiculo->estacion = estacion;

    return vehiculo;
}

static void generarPlaca(char placa[8]) // Static para privatizar el metodo
{

    for (int i = 0; i < 3 ; i++)
    {
        placa[i] = (char)('A' + rand() % 26);
    }
    placa[3] = ' ';
    for (int i = 4 ; i < 7 ; i++)
    {
        placa[i] = (char)('0' + rand() % 10);
    }
    placa[7] = '\0';
}

static int generarHora()
{
    int hora = rand() % 24;
    int minuto = rand() % 60;

    return hora * 100 + minuto;
}

static const TipoVehiculo generarTipoVehiculo () {
    float r = (float)rand() / (float)RAND_MAX; 

    if (r <= 0.1) return EMERGENCIA; 
    if( r <= 0.15) return MEDICO; 
    if (r <= 0.3) return PASAJEROS; 
    if (r <=0.5) return CARGA; 
    if (r <=0.7) return TAXI; 
    return PARTICULAR;

}

Vehiculo* generarVehiculoAleatorio()
{
    char placa[8];
    generarPlaca(placa);

    const char* estacion = estaciones[rand() % (sizeof(estaciones) / sizeof(estaciones[0]))];

    TipoVehiculo tipo = generarTipoVehiculo(); 
    DiaSemana dia = (DiaSemana)(rand() % 7);

    int sentido = (int)(0 + rand() % 2);
    int horaMilitar = generarHora();
    float tiempoTramo = (float)(20 + rand() % 20);

    if (tipo == CARGA){
        tiempoTramo += 25; 
    }

    if(tipo == EMERGENCIA){
        tiempoTramo -= 10;
    }

    return crearVehiculo(placa , tipo , sentido , horaMilitar , dia , tiempoTramo , estacion);
}



static const char* tipoVehiculoToString(TipoVehiculo t) 
{
    switch (t) {
        case EMERGENCIA: return "EMERGENCIA";
        case MEDICO:     return "MEDICO";
        case PASAJEROS:  return "PASAJEROS";
        case CARGA:      return "CARGA";
        case TAXI:       return "TAXI";
        case PARTICULAR: return "PARTICULAR";
        default:         return "DESCONOCIDO";
    }
}

static const char* diaToString(DiaSemana d) 
{
    switch (d) {
        case LUNES:     return "LUNES";
        case MARTES:    return "MARTES";
        case MIERCOLES: return "MIERCOLES";
        case JUEVES:    return "JUEVES";
        case VIERNES:   return "VIERNES";
        case SABADO:    return "SABADO";
        case DOMINGO:   return "DOMINGO";
        default:        return "DESCONOCIDO";
    }
}

static const char* sentidoToString(int sentido)
{
    return (sentido == 0) ? "Sur-Norte" : "Norte-Sur";
}

static void printHoraHHMM(int horaMilitar) 
{
    int hh = horaMilitar / 100;
    int mm = horaMilitar % 100;
    printf("%02d:%02d", hh, mm);
}

void imprimirVehiculo(const Vehiculo* v) 
{
    if (!v) {
        printf("(Vehiculo NULL)\n");
        return;
    }

    printf("=== VEHICULO ===\n");
    printf("Placa: %s\n", v->placa);
    printf("Tipo: %s\n", tipoVehiculoToString(v->tipo));
    printf("Sentido: %s (%d)\n", sentidoToString(v->sentido), v->sentido);

    printf("Hora: ");
    printHoraHHMM(v->horaMilitar);
    printf(" (%04d)\n", v->horaMilitar);

    printf("Dia: %s\n", diaToString(v->dia));
    printf("Tiempo tramo: %.2f min\n", v->tiempoTramo);
    printf("Estacion: %s\n", v->estacion ? v->estacion : "(sin estacion)");
    printf("==============\n");
}

void liberarvehiculo (Vehiculo* v) 
{
    free(v);
}
