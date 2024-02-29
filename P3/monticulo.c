/*
 * NOMBRE:
 * NOMBRE:
 * GRUPO:
 */
#include "monticulo.h"

void inicializarMonticulo(pmonticulo m) {
    m->ultimo = -1;
}

bool monticuloVacio(pmonticulo m) {
    return m->ultimo == -1;
}

void hundir(pmonticulo m, int i) {
    int hijoIzq, hijoDer, j, tmp;
    do {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        j = i;

        if (hijoDer <= m->ultimo && m->vector[hijoDer] < m->vector[i])
            i = hijoDer;
        if(hijoIzq <= m->ultimo && m->vector[hijoIzq] < m->vector[i])
            i = hijoIzq;

        tmp = m->vector[j];
        m->vector[j] = m->vector[i];
        m->vector[i] = tmp;
    } while (j != i);
}

int quitarMenor(pmonticulo m) {
    int x;
    if(monticuloVacio(m)) {
        printf("Error: Monticulo vacio\n");
        return 2*TAM;
    }
    else {
        x = m->vector[0];
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo--;
        if(m->ultimo > -1)
            hundir(m,0);
        return x;
    }
}

void crearMonticulo(int v[], int n, pmonticulo m) {
    int i;
    for (i = 0; i < n; i++)
        m->vector[i] = v[i];
    m->ultimo = n - 1;
    for (i = m->ultimo - 1 / 2; i >= 0; i--) //ERROR  muy leve , SI HUBIESE Q HACER FLOTAR ESTARÍA MAL , POR SELECCIONAR UNCORRECTAMENTE EL PADRE
        hundir(m, i);                        //EL NUMERO DE ITERACIONES EN ESTE CASO SERÍA UN MAS DE LA NECESARIA
                                             //EL ERROR YA ESTÁ CORREGIDO , CAMBIO i = m->ultimo / 2 POR i = m->ultimo - 1 / 2
}

void ordenarPorMonticulos(int v[], int n) {
    int i;
    pmonticulo monti = malloc(sizeof(struct monticulo));
    inicializarMonticulo(monti);

    crearMonticulo(v, n, monti);

    for(i = 0; i < n; i++) {
        v[i] = quitarMenor(monti);
    }
    free(monti);
}
