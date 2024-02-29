/*
 * NOMBRE:
 * NOMBRE:
 * GRUPO:
 */
#ifndef P3_MONTICULO_H
#define P3_MONTICULO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 256000

struct monticulo {
    int ultimo;
    int vector[TAM];
};

typedef struct monticulo * pmonticulo;

void crearMonticulo(int v[], int n, pmonticulo m);
int quitarMenor(pmonticulo m);
void ordenarPorMonticulos(int v[], int n);


void inicializarMonticulo(pmonticulo m);
bool monticuloVacio(pmonticulo m);
void hundir(pmonticulo m, int i);



#endif //P3_MONTICULO_H
