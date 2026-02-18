#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
#include "menu.h"
#include "helpers.h"
#include "ordenacion.h"
#include "limpiarData.h"



int main(void) {

    srand((unsigned int)time(NULL));
    

    // Caso normal, solo borrar los indicados por el enunciado

    FILE* f = fopen("tiempos.txt", "w");
     if (!f) {
        perror("No se pudo abrir tiempos.txt");
        return 1;
    }

    for(int n = 5000 ; n <= 100000 ; n += 5000 )
    {
        Lista* lista_original = NULL;
        Lista* copias[2] = {NULL, NULL};
                
        printf("=============================================\n");
        printf("  SISTEMA DE ORDENACION DE VEHICULOS\n");
        printf("=============================================\n\n");
            
        
        printf("\nGenerando %d vehiculos aleatorios...\n", n);
        lista_original = crear_lista();
        
        if (!lista_original) {
            printf("Error: No se pudo crear la lista\n");
            fclose(f);
            return 1;
        }
        int numeroVehiculosCarga = 0; 
        int vehiculos_generados = 0; 
        for (int i = 0; i < n; i++) {
            Vehiculo* v = generarVehiculoAleatorio();
            
            if (v) {
                if (v->tipo == CARGA) { 
                    numeroVehiculosCarga++;
                }
                if (insertar_al_inicio(lista_original, v)) {
                    vehiculos_generados++;
                } else {
                    liberarvehiculo(v);
                }
            }
        }
        printf("El numero de vehiculos de carga es: %d\n", numeroVehiculosCarga);
        if (vehiculos_generados == 0) {
            printf("Error: No se pudo generar ningun vehiculo\n");
            destruir_lista(lista_original);
            fclose(f);
            return 1;
        }
        
        printf("Lista original generada con %d vehiculos (de %d solicitadas)\n", 
            vehiculos_generados, n);
        
        // mostrarPrimerosVehiculos (lista_original, 5, "PRIMEROS VEHICULOS DE LA LISTA ORIGINAL"); 
        
        printf("\n=============================================\n");
        printf("Depurando los datos que sean de las estaciones centro o no esten en hora pico...\n");
        printf("=============================================\n");
        
        limpiarLista(lista_original);

        // mostrarPrimerosVehiculos (lista_original, 5, "PRIMEROS VEHICULOS DE LA LISTA DEPURADA");

        printf("\nCreando copias de la lista para cada algoritmo...\n");
        copias[0] = copiar_lista(lista_original);
        copias[1] = copiar_lista(lista_original);
        
        // Validar copias
        if (!copias[0] || !copias[1]) {
            printf("Error: No se pudieron crear copias\n");
            destruir_lista(lista_original);
            if (copias[0]) destruir_lista(copias[0]);
            if (copias[1]) destruir_lista(copias[1]);
            fclose(f);
            return 1;
        }
        
        printf("\n=============================================\n");
        printf("MEDICION DE TIEMPOS DE ORDENACION\n");
        printf("=============================================\n");
        
        double tiempos[2] = {0};
        
        tiempos[0] = medir_tiempo_ordenacion(copias[0], ordenar_mergesort, "MergeSort");
        tiempos[1] = medir_tiempo_ordenacion(copias[1], ordenar_quicksort, "QuickSort");
        
        fprintf(f, "%d\n%.10f\n%.10f\n", n, tiempos[0], tiempos[1]);
        fflush(f); 
        
        printf("\nVerificando consistencia de resultados...\n");
        if (listas_son_iguales(copias[0], copias[1])) {
            printf("✓ Todas las listas ordenadas son identicas\n");
        } else {
            printf("✗ ADVERTENCIA: Las listas ordenadas no son identicas\n");
        }

        
        // mostrarPrimerosVehiculos(copias[0] , 5 , "Primeros de la copia del mergesort");
        // mostrarPrimerosVehiculos(copias[1] , 5 , "Primeros de la copia del quicksort");

        // Liberar memoria
        printf("\nLiberando memoria...\n");
        destruir_lista(lista_original);
        for (int i = 0; i < 2; i++) {
            if (copias[i]) destruir_lista(copias[i]);
        }
    }

    // Caso especial, eliminar tambien el 20% mas lento

    // FILE* f = fopen("tiempos20.txt", "w");
    // if (!f) {
    //     perror("No se pudo abrir tiempos.txt");
    //     return 1;
    // }

    // for(int n = 5000 ; n <= 100000 ; n += 5000 )
    // {
    //     Lista* lista_original = NULL;
    //     Lista* copias[2] = {NULL, NULL};
                
    //     printf("=============================================\n");
    //     printf("  SISTEMA DE ORDENACION DE VEHICULOS\n");
    //     printf("=============================================\n\n");
            
        
    //     printf("\nGenerando %d vehiculos aleatorios...\n", n);
    //     lista_original = crear_lista();
        
    //     if (!lista_original) {
    //         printf("Error: No se pudo crear la lista\n");
    //         fclose(f);
    //         return 1;
    //     }
        
    //     int vehiculos_generados = 0;
    //     for (int i = 0; i < n; i++) {
    //         Vehiculo* v = generarVehiculoAleatorio();
    //         if (v) {
    //             if (insertar_al_final(lista_original, v)) {
    //                 vehiculos_generados++;
    //             } else {
    //                 liberarvehiculo(v);
    //             }
    //         }
    //     }
        
    //     if (vehiculos_generados == 0) {
    //         printf("Error: No se pudo generar ningun vehiculo\n");
    //         destruir_lista(lista_original);
    //         fclose(f);
    //         return 1;
    //     }
        
    //     printf("Lista original generada con %d vehiculos (de %d solicitadas)\n", 
    //         vehiculos_generados, n);
        
    //     // mostrarPrimerosVehiculos (lista_original, 5, "PRIMEROS VEHICULOS DE LA LISTA ORIGINAL"); 
        
    //     printf("\n=============================================\n");
    //     printf("Depurando los datos que sean de las estaciones centro o no esten en hora pico...\n");
    //     printf("=============================================\n");
        
    //     limpiarLista(lista_original);
    //     limpiarLista20MasLentos(lista_original);

    //     // mostrarPrimerosVehiculos (lista_original, 5, "PRIMEROS VEHICULOS DE LA LISTA DEPURADA");

    //     printf("\nCreando copias de la lista para cada algoritmo...\n");
    //     copias[0] = copiar_lista(lista_original);
    //     copias[1] = copiar_lista(lista_original);
        
    //     // Validar copias
    //     if (!copias[0] || !copias[1]) {
    //         printf("Error: No se pudieron crear copias\n");
    //         destruir_lista(lista_original);
    //         if (copias[0]) destruir_lista(copias[0]);
    //         if (copias[1]) destruir_lista(copias[1]);
    //         fclose(f);
    //         return 1;
    //     }
        
    //     printf("\n=============================================\n");
    //     printf("MEDICION DE TIEMPOS DE ORDENACION\n");
    //     printf("=============================================\n");
        
    //     double tiempos[2] = {0};
        
    //     tiempos[0] = medir_tiempo_ordenacion(copias[0], ordenar_mergesort, "MergeSort");
    //     tiempos[1] = medir_tiempo_ordenacion(copias[1], ordenar_quicksort, "QuickSort");
        
    //     fprintf(f, "%d\n%.10f\n%.10f\n", n, tiempos[0], tiempos[1]);
    //     fflush(f); 
        
    //     printf("\nVerificando consistencia de resultados...\n");
    //     if (listas_son_iguales(copias[0], copias[1])) {
    //         printf("✓ Todas las listas ordenadas son identicas\n");
    //     } else {
    //         printf("✗ ADVERTENCIA: Las listas ordenadas no son identicas\n");
    //     }
        
    //     // mostrarPrimerosVehiculos(copias[0] , 5 , "Primeros de la copia del mergesort");
    //     // mostrarPrimerosVehiculos(copias[1] , 5 , "Primeros de la copia del quicksort");

    //     // Liberar memoria
    //     printf("\nLiberando memoria...\n");
    //     destruir_lista(lista_original);
    //     for (int i = 0; i < 2; i++) {
    //         if (copias[i]) destruir_lista(copias[i]);
    //     }
    // }

    fclose(f);
    printf("Programa finalizado correctamente.\n");
    return 0;
}