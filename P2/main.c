/*
 * NOMBRE:
 * NOMBRE:
 * GRUPO:
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <stdbool.h>
#define MAX 256000
#define TEST 20

//ALGORITMOS DE ORDENACION

void ord_ins (int v [], int n) {
    int i, x, j;
    for (i = 1; i < n ; i++) {
        x = v[i];
        j = i - 1;
        while(j >= 0 && v[j] > x) {
            v [j + 1] = v [j];
            j -= 1;
        }
        v [j + 1] = x;
    }
}


void ord_shell (int v [], int n) {
    int incremento, i, j, tmp;
    bool seguir;
    incremento = n;

    do {
        incremento /= 2;
        for (i = incremento; i < n; i++) {
            tmp = v[i];
            j = i;
            seguir = true;
            while (j - incremento >= 0 && seguir) {
                if(tmp < v[j - incremento]) {
                    v[j] = v[j - incremento];
                    j = j -  incremento;
                }
                else
                    seguir = false;
            }
            v[j] = tmp;
        }
    } while(incremento != 0);
}

//FUNCIONES AUXILIARES
void listarVector(int v[] , int n){
    int i;
    printf("[");
    for (i = 0; i < n; ++i) {
        printf(" %d " , v[i]);
    }
    printf("]\n");
}

void estaOrdenado(int const v[] , int n){
    int i , ant;
    ant = v[0];
    for (i = 0; i < n; ++i) {
        if(ant <= v[i]){
            ant = v[i];
        }else{
            printf("Vector no ordenado\n");
            return;
        }
    }
    printf("Vector ordenado\n");
}

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
    int i , val;
    val = n - 1;
    for (i = 0; i < n; ++i) {
        v[i] = val;
        val--;
    }
}


void elegir(int v[], char iniVector , int n){

    if (iniVector == 'R') {
        aleatorio(v, n);
    } else if (iniVector == 'A') {
        iniciarVAscendente(v, n);
    } else if (iniVector == 'D') {
        iniciarVDescendente(v, n);
    }
}

char caso(int j){
    switch (j) {
        case 0:
        case 1:
            return 'R';//r de random
        case 2:
        case 3:
            return 'D';
        case 4:
        case 5:
            return 'A';//a de ascendente
        default:
            return 'F';
    }
}


double EstimadaIns(int n , char Ordenacion , int type){
    //Ordenacion = tipo vector inicial , type = cota a Estimar
    switch (Ordenacion) {
        case 'R': case 'D':
            switch (type) {
                case 0: return pow(n , 2);
                case 1: return pow(n , 1.8);
                case 2: return pow(n , 2.1);
                default: break;
            }
        case 'A':
            switch (type) {
                case 0: return n;
                case 1: return pow(n , 0.8);
                case 2: return pow(n ,1.2);
                default: break;
            }
        default:
            return 0;
    }
}


double EstimadaShell(int n, char Ordenacion , int type){ //Ordenacion = tipo vector inicial , type = cota a Estimar


    switch (Ordenacion) {
        case 'D':case 'A':
            switch (type) {
                case 0: return n * log(n);//estimada
                case 1: return n;//subestimada
                case 2: return pow(n , 1.3);//sobrestimada
                default: break;
            }
        case 'R':
            switch (type) {
                case 0: return pow(n, 1.2);//estimada
                case 1: return pow(n , 1.1);//subestimada
                case 2: return pow(n , 1.3);//sobrestimada
                default: break;
            }
        default:
            return 0;
    }
}

double medicion(int j , int n , char Ordenacion, int v[]){
    double ta, td, t1 , t2;
    ta = microsegundos();
    elegir(v , Ordenacion , n);
    (j % 2 == 0) ? ord_ins(v , n) : ord_shell(v , n);
    td = microsegundos();
    t1 = td - ta;
    ta = microsegundos();
    elegir(v , Ordenacion , n);
    td = microsegundos();
    t2 = td - ta;
    return t1 - t2;
}

double medicionMenor500(int j, int n,char Ordenacion,int v[],int k){
    int i;
    double ta , td , t1, t2;
    printf("(*)");
    ta = microsegundos();
    for (i = 0; i < k; ++i) {
        elegir(v , Ordenacion , n);
        (j % 2 == 0) ? ord_ins(v , n) : ord_shell(v , n);
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

void imprimirCabecera(int j){
    switch (j) {
        case 0:
            printf("\n Vector Aleatorio Insercion\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.1");
            break;
        case 1:
            printf("\n Vector Aleatorio Shell\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n^1.2","t(n)/n^1.3");
            break;
        case 2:
            printf("\n Vector Descendente Insercion\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n^1.8","t(n)/n^2","t(n)/n^2.1");
            break;
        case 3:
            printf("\n Vector Descendente Shell\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.3");
            break;
        case 4:
            printf("\n Vector Ascendente Insercion\n");
            printf("%20s%20s%20s%20s%20s\n",
                   "n","t(n)","t(n)/n^0.8","t(n)/n","t(n)/n^1.2");
            break;
        case 5:
            printf("\n Vector Ascendente Shell\n");
            printf("%20s%20s%20s%25s%20s\n",
                   "n","t(n)","t(n)/n","t(n)/n/*log(n)","t(n)/n^1.3");
            break;
        default:
            break;
    }
}

//TEST
void tests(int v[]) {
    int i, j;

    for ( i = 0 ; i < 3; i++) {
        for ( j = 0 ; j < 2; j++) {

            elegir(v , caso(i * 2) , TEST);

            j == 0 ? printf("\nSHELL\n") : printf("\nINSERCION\n");

            listarVector(v, TEST);
            estaOrdenado(v, TEST);

            j == 0 ? ord_shell(v, TEST) : ord_ins(v, TEST);

            listarVector(v, TEST);
            estaOrdenado(v, TEST);
        }
    }
}

void tiempos(int v[]){
    int n , j , k = 1000;
    double t, cotaSub , cotaSobr , cotaEst;
    char Ordenacion;
    printf("\nMedicion de tiempos\n");
    for( j = 0 ; j < 6 ; j++){
        if(j == 4)  k = 5000;
        Ordenacion = caso(j);
        if(Ordenacion == 'F')return;
        imprimirCabecera(j);
        for(n = 500 ; n <= ( j % 2 == 0 ? 64000 : 256000) ; n *= 2){
            t = medicion(j , n , Ordenacion , v);
            if(t < 500){
                t = medicionMenor500 (j, n , Ordenacion , v, k);
            }else
                printf("   ");
            if(j % 2 == 0){
                cotaEst = EstimadaIns(n , Ordenacion , 0 );
                cotaSub = EstimadaIns(n  , Ordenacion , 1 );
                cotaSobr = EstimadaIns(n  , Ordenacion , 2 );
            }else{
                cotaEst = EstimadaShell(n , Ordenacion , 0 );
                cotaSub = EstimadaShell(n  , Ordenacion , 1 );
                cotaSobr = EstimadaShell(n  , Ordenacion , 2 );
            }
            printf("%20d%20.8lf%20.8lf%20.8lf%20.8lf\n",n ,t ,t / cotaSub,
                   t / cotaEst,t / cotaSobr);
        }
        printf("\n\n");
    }
}

int main() {
    int v[MAX];
    inicializarSemilla();
    tests(v);
    tiempos(v);
}
