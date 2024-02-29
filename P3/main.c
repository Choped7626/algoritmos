/*
 * NOMBRE:
 * NOMBRE:
 * GRUPO:
 */
#include "monticulo.h"
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define TEST 10

//FUNCIONES AUXILIARES:

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

void listarMonticulo(pmonticulo mon) {
    int i;
    for (i = 0; i <= mon->ultimo; i++)
        printf("%d ", mon->vector[i]);
    printf("\n");
}
void listarVector(int v[] , int n){
    int i;
    printf("[");
    for (i = 0; i < n; ++i) {
        printf(" %d " , v[i]);
    }
    printf("]\n");
}



//MEDICION
void imprimirCabecera(int j) {
    switch (j) {
        case 0:
            printf("\nCrear Monticulo\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
            break;
        case 1:
            printf("\nVector Ascendente\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.5");
            break;
        case 2:
            printf("\nVector Descendente\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.5");
            break;
        case 3:
            printf("\nVector Aleatorio\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.5");
            break;
        default: break;
    }
}

char caso(int j) {
    switch (j) {
        case 0:
            return 'C'; //CREAR ALEATORIO
        case 1:
            return 'A'; //ASCENDENTE
        case 2:
            return 'D'; //DESCENDENTE
        case 3:
            return 'R'; //ALEATORIO
        default:
            return 'F';
    }
}

double Estimada(int n, char Ordenacion, int type) {
    switch (Ordenacion) {
            case 'C':
                switch (type) {
                    case 0: return n;//estimada
                    case 1: return pow(n, 0.8);//subestimada
                    case 2: return pow(n, 1.2);//sobrestimada
                    default:break;
                }
            case 'A': case 'D':case 'R':
                switch (type) {
                    case 0: return n*log(n);//estimada
                    case 1: return n;//subestimada
                    case 2: return pow(n, 1.5);//sobrestimada
                    default:break;
                }
        default:
            return 0;
    }
}

void elegir(int v[], char iniVector , int n){

    if (iniVector == 'C' || iniVector ==     'R') {
        aleatorio(v, n);
    } else if (iniVector == 'A') { ///
        iniciarVAscendente(v, n);
    } else if (iniVector == 'D') { ///
        iniciarVDescendente(v, n);
    }
}

double medicion(int j , int n , char Ordenacion, int v[], pmonticulo mon){
    double ta, td, t1;
    elegir(v , Ordenacion , n);
    ta = microsegundos();
    (j == 0) ? crearMonticulo(v, n, mon) : ordenarPorMonticulos(v, n);  ///
    td = microsegundos();
    t1 = td - ta;
    return t1;
}

double medicionMenor500(int j, int n,char Ordenacion,int v[],int k, pmonticulo mon) {
    int i;
    double ta, td, t1 , t2;
    printf("(*)");
    ta = microsegundos();
    for (i = 0; i < k; ++i) {
        elegir(v, Ordenacion, n);
        inicializarMonticulo(mon);
        (j == 0) ? crearMonticulo(v, n, mon) : ordenarPorMonticulos(v, n);  ///
    }
    td = microsegundos();
    t1 = td - ta;
    ta = microsegundos();
    for (i = 0; i < k; i++) {
        elegir(v , Ordenacion , n);
        inicializarMonticulo(mon);
    }
    td = microsegundos();
    t2 = td - ta;
    return ((t1 - t2) / (double)k);
}

void tiempos(int v[], pmonticulo mon){
    int n , j , k = 1000;
    double t, cotaSub , cotaSobr , cotaEst;
    char Ordenacion;
    printf("\nMedicion de tiempos\n");
    for( j = 0 ; j < 4 ; j++){   ///
        Ordenacion = caso(j);
        if(Ordenacion == 'F') return;
        imprimirCabecera(j);
        for(n = 500 ; n <= TAM ; n *= 2){
            inicializarMonticulo(mon);
            t = medicion(j , n , Ordenacion , v, mon);
            if(t < 500){
                t = medicionMenor500 (j, n , Ordenacion , v, k, mon);
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


//TEST

void cabeceras_test(int i) {
    switch (i) {
        case 1:
            printf("Monticulo Ascendente\n");
            break;
        case 2 :
            printf("Monticulo Descendente\n");
            break;
        case 3:
            printf("Monticulo con vector aleatorio\n");
            break;
        default:
            break;
    }
}

void test(int v[], pmonticulo mon1) {
    int i;
    for (i = 1; i < 4; i++) {
        caso(i);
        inicializarMonticulo(mon1);
        elegir(v, caso(i), TEST);
        cabeceras_test(i);
        listarVector(v, TEST);
        crearMonticulo(v, TEST, mon1);
        listarMonticulo(mon1);
        ordenarPorMonticulos(v, TEST);
        printf("Vector ordenado\n");
        listarVector(v, TEST);
        printf("\n");
    }
}

int main() {

    inicializarSemilla();
    int v[TEST];
    int c[TAM];
    pmonticulo mon = malloc(sizeof(struct monticulo));

    tiempos(c, mon);
    test(v, mon);
    free(mon);

    return 0;

}
