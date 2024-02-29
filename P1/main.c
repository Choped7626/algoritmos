#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define MAX 256000

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}


int sumaSubMax1(int v[], int n){
    int sumaMax = 0;
    int estaSuma , i , j;
    for (i = 0; i < n; ++i) {
        estaSuma = 0;
        for (j = i; j < n; ++j) {
            estaSuma = estaSuma + v[j];
            if(estaSuma > sumaMax){
                sumaMax = estaSuma;
            }
        }
    }
    return sumaMax;
}

int sumaSubMax2(int v[] , int n){
    int estaSuma = 0; int sumaMax = 0; int j;
    for (j = 0; j < n; ++j) {
        estaSuma = estaSuma + v[j];
        if(estaSuma > sumaMax){
            sumaMax = estaSuma;
        }else if(estaSuma < 0){
            estaSuma = 0;
        }
    }
    return sumaMax;
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

void listarVector(int v[] , int n){
    int i;
    printf("[");
    for (i = 0; i < n; ++i) {
        printf(" %d " , v[i]);
    }
    printf("]\n");
}


void test1(){
    int a[] = {-9, 2, -5, -4, 6};
    int size = sizeof(a) / sizeof(a[0]);
    listarVector(a, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(a, size), sumaSubMax2(a, size));

    int b[] = {4, 0, 9, 2, 5};
    listarVector(b, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(b, size), sumaSubMax2(b, size));

    int c[] = {-2, -1,-9, -7, -1};
    listarVector(c, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(c, size), sumaSubMax2(c, size));

    int d[] = {9, -2, 1, -7, -8};
    listarVector(d, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(d, size), sumaSubMax2(d, size));

    int e[] = {15, -2, -5, -4, 16};
    listarVector(e, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(e, size), sumaSubMax2(e, size));

    int f[] = {7, -5, 6, 7, -7};
    listarVector(f, size);
    printf("\t\t1: %d  2:  %d\n",sumaSubMax1(f, size), sumaSubMax2(f, size));
}

void test2(){
    int i, a, b;
    int v[9];
    printf("test2\n");
    printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i=0; i < 10; i++) { //bucle de comparacion , cantos ejemplos facer
        aleatorio(v, 9);
        listarVector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%33s%15d%15d\n", "" , a , b);
    }
}


void tiempos_Suma1(int v[]) {
    int n;
    int k = 1000;
    int i;
    double ta , td , t , t1 , t2;
    double cotaSub , cotaSobr , cotaEst;

    printf("SumaSubMax 1\n");
    printf("   %33s%33s%33s%33s%33s\n" , "n" , "t(n)" , "t(n)/n^1.6" , "t(n)/n^2" , "t(n)/n^2.2");
    for(n = 500 ; n <= 32000 ; n *= 2){
        inicializarSemilla();
        aleatorio(v , n);
        ta = microsegundos();
        sumaSubMax1(v , n);
        td = microsegundos();
        t = td - ta;
        if(t < 500){
            printf("(*)");
            ta = microsegundos();
            for (i = 0; i < k; ++i) {
                aleatorio(v , n);
                sumaSubMax1(v , n);
            }
            td = microsegundos();
            t1 = td - ta;
            ta = microsegundos();
            for (i = 0; i < k; ++i) {
                aleatorio(v , n);
            }
            td = microsegundos();
            t2 = td - ta;
            t = (t1 - t2) / k;
        }else
            printf("   ");
        cotaEst = pow(n , 2);
        cotaSub = pow(n , 1.6);
        cotaSobr = pow(n , 2.20);
        printf("%33d%33lf%33lf%33lf%33lf\n" , n , t , t/cotaSub , t/cotaEst , t/cotaSobr );
    }
}



void tiempos_Suma2(int v[]) {
    int n;
    int k = 1000;
    int i;
    double ta , td , t , t1 , t2;
    double cotaSub , cotaSobr , cotaEst;

    printf("SumaSubMax 2\n");
    printf("   %33s%33s%33s%33s%33s\n" , "n" , "t(n)" , "t(n)/n^0.5" , "t(n)/n" , "t(n)/nlog(n)");
    for(n = 500 ; n <= 256000 ; n *= 2){
        inicializarSemilla();
        aleatorio(v , n);
        ta = microsegundos();
        sumaSubMax2(v , n);
        td = microsegundos();
        t = td - ta;
        if(t < 500){
            printf("(*)");
            ta = microsegundos();
            for (i = 0; i < k; ++i) {
                aleatorio(v , n);
                sumaSubMax2(v , n);
            }
            td = microsegundos();
            t1 = td - ta;
            ta = microsegundos();
            for (i = 0; i < k; ++i) {
                aleatorio(v , n);
            }
            td = microsegundos();
            t2 = td - ta;
            t = (t1 - t2) / k;
        }else
            printf("   ");
        cotaEst = pow(n , 1);
        cotaSub = pow(n , 0.5);
        cotaSobr = n * log(n);
        printf("%33d%33lf%33lf%33lf%33lf\n" , n , t , t/cotaSub , t/cotaEst , t/cotaSobr );
    }
}


int main() {

    int v[MAX];

    tiempos_Suma1(v);



}
