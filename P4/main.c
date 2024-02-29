#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define TAM_MAX 1000
#define TAM_FIG2 5
#define TAM_FIG3 4
#define TIEMPOS 1024

typedef int ** matriz;

void dijkstra(matriz grafo, matriz distancias, int tam) {
    int n, i, j, min, v = 0, x;
    int *noVisitados = malloc(tam * sizeof(int));
    for (n = 0; n < tam; n++) {
        for (i = 0; i < tam; i++) {
            noVisitados[i] = 1;
            distancias [n][i] = grafo[n][i];
        }
        noVisitados[n] = 0;
        j = 0;
        while (j < tam - 2) {
            min = TAM_MAX;
            for(x = 0; x < tam; x++) {
                if (noVisitados[x] == 1) {
                    if(distancias[n][x] < min) {
                        min = distancias[n][x];
                        v = x;
                    }
                }
            }
            noVisitados[v] = 0;
            for (x = 0; x < tam; x++){
                if(noVisitados[x] == 1) {
                    if(distancias[n][x] >(distancias[n][v] + grafo[v][x])) {
                        distancias[n][x] = distancias[n][v] + grafo[v][x];
                    }
                }
            }
            j++;
        }
    }
    free(noVisitados);
}


//Funciones figura 4
matriz crearMatriz(int n) {
    int i;
    matriz aux;
    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}
/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
no dirigido con n nodos, representado por su matriz de adayencia */

void iniMatriz(matriz m, int n) {
    int i, j;
    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % TAM_MAX + 1;
    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberarMatriz(matriz m, int n) {
    int i;
    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}



//Funciones auxiliares
double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.000);
}

void inicializarSemilla(){
    srand(time(NULL));
}

void listar_matriz(matriz m, int size) {
    int i, j;
    for(i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            printf("%2d ", m[i][j]);
        }
        printf("\n");
    }
}

//Test para las matrices de las figuras 2 y 3

void mostrar_informacion(matriz m, int size) {
    matriz dist_min = crearMatriz(size);
    dijkstra(m, dist_min, size);
    printf("MATRIZ DE ADYACENCIA\n");
    listar_matriz(m, size);
    printf("MATRIZ DE DISTANCIA MINIMA\n");
    listar_matriz(dist_min, size);
    liberarMatriz(m,size);
    liberarMatriz(dist_min, size);
}

void testFigura2() {
    int i, j;
    matriz figura2 = crearMatriz(TAM_FIG2);

    figura2[0][1] = 1;
    figura2[0][2] = 8;
    figura2[0][3] = 4;
    figura2[0][4] = 7;

    figura2[1][2] = 2;
    figura2[1][3] = 6;
    figura2[1][4] = 5;

    figura2[2][3] = 9;
    figura2[2][4] = 5;
    figura2[3][4] = 3;

    for (i=0; i<TAM_FIG2; i++) {
        for (j = 0; j <= i; j++) {
            if (i == j)
                figura2[i][j] = 0;
            else
                figura2[i][j] = figura2[j][i];
        }
    }

    printf("FIGURA 2\n");
    mostrar_informacion(figura2, TAM_FIG2);
}

void testFigura3() {
    int i, j;
    matriz figura3 = crearMatriz(TAM_FIG3);

    figura3[0][1] = 1;
    figura3[0][2] = 4;
    figura3[0][3] = 7;

    figura3[1][2] = 2;
    figura3[1][3] = 8;

    figura3[2][3] = 3;

    for (i=0; i<TAM_FIG3; i++) {
        for (j = 0; j <= i; j++) {
            if (i == j)
                figura3[i][j] = 0;
            else
                figura3[i][j] = figura3[j][i];
        }
    }
    printf("\nFIGURA 3\n");
    mostrar_informacion(figura3, TAM_FIG3);
}

//Tiempos

double medicionMenor500(int n, int k, matriz aleatoria, matriz dist_min) {
    int i, x;
    double ta, td, t1 , t2;
    printf("(*)");
    ta = microsegundos();
    for (i = 0; i < k; i++) {
        iniMatriz(aleatoria, n);
        dijkstra(aleatoria, dist_min, n);
    }
    td = microsegundos();
    t1 = td - ta;
    ta = microsegundos();
    for (x = 0; x < k; x++) {
        iniMatriz(aleatoria, n);
    }
    td = microsegundos();
    t2 = td - ta;
    return ((t1 - t2) / k);
}

void tiempos(){
    int n , k = 1000;
    double ta, td, t, cotaSub , cotaSobr , cotaEst;
    matriz aleatoria = crearMatriz(TIEMPOS);
    matriz dist_min = crearMatriz(TIEMPOS);

    printf("\nMedicion de tiempos\n");
    printf("%20s%20s%20s%20s%20s\n",
           "n","t(n)","t(n)/n^2.5","t(n)/n^2.78","t(n)/n^3");
    for(n = 8 ; n <= TIEMPOS ; n*=2){
        iniMatriz(aleatoria, n);
        ta = microsegundos();
        dijkstra(aleatoria, dist_min, n);
        td = microsegundos();
        t = td - ta;
        if(t < 500) {
            t = medicionMenor500(n, k, aleatoria, dist_min);
        }
        else
            printf("   ");

        cotaEst = pow(n, 2.78);
        cotaSub = pow(n, 2.5);
        cotaSobr = pow(n, 3);

        printf("%20d%20.8lf%20.8lf%20.8lf%20.8lf\n", n , t , t / cotaSub,
               t / cotaEst,t / cotaSobr);
    }
        printf("\n\n");
    liberarMatriz(aleatoria, TIEMPOS);
    liberarMatriz(dist_min, TIEMPOS);
}




int main() {
    testFigura2();
    //testFigura3();
    tiempos();
}
