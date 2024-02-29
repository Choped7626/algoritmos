#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 64000
#define TEST 15

/*
ALGORITMOS EXAMEN

NOMBRE: Mario Lamas Angeriz	LOGIN: m.lamasa@udc.es

GRUPO : 3.2	

FECHA : 18/01/2024
*/

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.000);
}

void inicializarSemilla(){
    srand(time(NULL));
}

void aleatorio(int v[] , int n){
    int i , m = 2 * n + 1;
    for (i = 0; i < n ; i++) {
        v[i] = (rand() % m) - n;
    }
}

void iniciarVAscendente(int v[] , int n){
    int i;
    for (i = 0; i < n ; i++) {
        v[i] = i;
    }
}

void iniciarVDescendente(int v[] , int n){
    int i;
    for (i = 0; i < n; ++i) {
        v[i] = n - i;
    }
}

void auxOrd (int v[] , int izq ,int der){
    int i , j , piv;
    int aux;
    if (izq < der){
        piv = v[izq+1];
        //intercambiar
        aux = v[izq];
        v[izq] = v[izq + 1];
        v[izq + 1] = aux;
        //intercambiar
        i = izq + 1;
        j = der;
        while (i <= j){
            while (i <= der && v[i] < piv) i++;
            while (v[j] > piv) j--;
            if(i <= j){
                //
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                //
                i++;
                j--;
            }
        }
        //
        aux = v[izq];
        v[izq] = v[j];
        v[j] = aux;
        //
        auxOrd(v , izq , j-1);
        auxOrd(v , j+1 , der);
    }
}

void ordenar (int v[] , int n){
    auxOrd(v , 0 , n-1);
}

char caso(int j) {
    switch (j) {
        case 0:
            return 'R'; //CREAR ALEATORIO
        case 1:
            return 'A'; //ASCENDENTE
        case 2:
            return 'D'; //DESCENDENTE
        default:
            return 'F';
    }
}

void elegir(int v[], char iniVector , int n){

    if (iniVector ==     'R') {
        aleatorio(v, n);
    } else if (iniVector == 'A') {
        iniciarVAscendente(v, n);
    } else if (iniVector == 'D') {
        iniciarVDescendente(v, n);
    }
}

void cabeceras_test(int i) {
    switch (i) {
        case 0:
            printf("Vector aleatorio\n");
            break;
        case 1:
            printf("Vector Ascendente\n");
            break;
        case 2:
            printf("Vector Descendente\n");
            break;
        default:
            break;
    }
}

void listarVector(int v[] , int n){
    int i;
    for (i = 0; i < n ; i++)
        printf("%d " , v[i]);
    printf("\n");
}

void test(int v[]){
    int i;
    for (i = 0; i < 3; i++) {
        elegir(v, caso(i), TEST);
        cabeceras_test(i);
        listarVector(v, TEST);
        ordenar(v , TEST);
        printf("Vector ordenado\n");
        listarVector(v, TEST);
        printf("\n");
    }
}

void imprimirCabecera(int j) {
    switch (j) {
        case 0:
            printf("\nVector Aleatorio\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/nlog(n)","t(n)/n^1.5");
            break;
        case 1:
            printf("\nVector Ascendente\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n^1.8","t(n)/n^2.0","t(n)/n^2.1");
            break;
        case 2:
            printf("\nVector Descendente\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/nlog(n)","t(n)/n^2.0","t(n)/n^2.2");
            break;
        default: break;
    }
}

double medicion(int j , int n , char Ordenacion, int v[]){
    double ta, td, t1;
    elegir(v , Ordenacion , n);
    ta = microsegundos();
    ordenar(v , n);
    td = microsegundos();
    t1 = td - ta;
    return t1;
}

double medicionMenor500(int j, int n,char Ordenacion,int v[],int k){
    int i;
    double ta , td , t1, t2;
    printf("(*)");
    ta = microsegundos();
    for (i = 0; i < k; ++i) {
        elegir(v , Ordenacion , n);
        ordenar(v , n);
    }
    td = microsegundos();
    t1 = td - ta;
    ta = microsegundos();
    for (i = 0; i < k; i++) {
        elegir(v , Ordenacion , n);
    }
    td = microsegundos();
    t2 = td - ta;
    return ((t1 - t2) / (double)k);
}

double Estimada(int n, char Ordenacion, int type) {
    switch (Ordenacion) {
        case 'R':
            switch (type) {
                case 0: return n * log(n);  ///
                case 1: return n;           ///
                case 2: return pow(n , 1.5);///
                default:
                    return 0;
            }
            break;
        case 'A':
            switch (type) {
                case 0: return pow( n , 2);     ///
                case 1: return pow( n , 1.8);   ///
                case 2: return pow( n , 2.1);    ///
                default:
                    return 0;
            }
            break;
        case 'D':
            switch (type) {
                case 0: return pow(n , 2);    ///
                case 1: return n * log(n);    ///
                case 2: return pow(n , 2.2);    ///
                default:
                    return 0;
            }
            break;
        default:
            return 0;
    }
}

void tiempos(int v[]){
    int n , j , k = 1000;
    double t, cotaSub , cotaSobr , cotaEst;
    char Ordenacion;
    printf("\nMedicion de tiempos\n");
    for( j = 0 ; j < 3 ; j++){   ///
        Ordenacion = caso(j);
        if(Ordenacion == 'F') return;
        imprimirCabecera(j);
        for(n = 500 ; n <= MAX ; n *= 2){
            t = medicion(j , n , Ordenacion , v);
            if(t < 500){
                t = medicionMenor500 (j, n , Ordenacion , v, k);
            }else
                printf("   ");

            cotaEst = Estimada(n , Ordenacion , 0 );
            cotaSub = Estimada(n  , Ordenacion , 1 );
            cotaSobr = Estimada(n  , Ordenacion , 2 );

            printf("%20d%20.8lf%20.8lf%20.8lf%20.8lf\n",n ,t ,t / cotaSub,
                   t / cotaEst,t / cotaSobr);
        }
        printf("\n\n");
    }
}

int main() {
    inicializarSemilla();
    int v[MAX];
    test(v);
    tiempos(v);
}
