#ifndef GENERADOR_H
#define GENERADOR_H

typedef enum { EMERGENCIA, MEDICO, PASAJEROS, CARGA, TAXI, PARTICULAR } TipoVehiculo;
typedef enum { LUNES, MARTES, MIERCOLES, JUEVES, VIERNES, SABADO, DOMINGO } DiaSemana; 

typedef struct
{
    char placa[8];
    TipoVehiculo tipo;
    int sentido;       // 0: Sur-Norte, 1: Norte-Sur
    int horaMilitar;  // Ej: 0730, 1845
    DiaSemana dia;
    float tiempoTramo; // Tiempo registrado en minutos
    const char* estacion;
} Vehiculo;

Vehiculo* crearVehiculo(const char* placa , TipoVehiculo tipo , int sentido , int horaMilitar , DiaSemana dia , float tiempoTramo , const char* estacion);
Vehiculo* generarVehiculoAleatorio();
void imprimirVehiculo(const Vehiculo* v);
void liberarvehiculo (Vehiculo* v);

#endif