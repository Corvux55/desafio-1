#include "util.h"
#include <cstdlib>
#include <ctime>

void iniciarAleatorio(){
    srand(time(0));
}
unsigned char fichaAleatoria(){
    return(rand()%6)+1;
}
int dimensionesValidas(int filas, int columnas){
    if (filas <=0 || columnas <=0){
        return 0;
    }
    if (filas > 100 || columnas > 100){
        return 0;
    }
    return 1;
}
int coordenadasValidas(int fila, int columna, int filas, int columnas){
    if (fila <0 || fila >= filas){
        return 0;
    }
    if (columna < 0 || columna >= columnas){
        return 0;
    }
    return 1;
}
int calcularbytes(int filas, int columnas){
    int bitsTotales = filas*columnas *3;
    int bytes = bitsTotales /8;
    if (bitsTotales %8 !=0){
        bytes++;
    }
    return bytes;
}