#include "tablero.h"
#include "util.h"
#include "memoria.h"

unsigned char obtenerFicha(unsigned char *tablero, int columnas, int fila, int columna){
    int indice = (fila * columnas + columna)*3;
    int byteActual= indice/8;
    int desplazamiento = indice%8;
    if (desplazamiento +3 <=8){
        unsigned  char mascara =7 << desplazamiento;
        return (tablero[byteActual] & mascara) >> desplazamiento;
    }
    int bitsEnByte0= 8- desplazamiento;
    int bitsEnByte1 = 3- bitsEnByte0;
    unsigned char mascara0 = (1<< bitsEnByte0)-1;
    unsigned char parte0= (tablero[byteActual] >> desplazamiento & mascara0);
    unsigned char mascara1 = (1 << bitsEnByte1)-1;
    unsigned char parte1 = tablero[byteActual +1] & mascara1;
    return parte0 | (parte1 << bitsEnByte0);
}
void escribirFicha(unsigned char *tablero,int columnas, int fila, int columna, unsigned char valor){
    int indice = (fila * columnas + columna) * 3;
    int byteActual= indice/8;
    int desplazamiento = indice%8;
    valor = valor & 7;
    if (desplazamiento +3 <=8){
        unsigned  char mascara =7 << desplazamiento;
        tablero[byteActual] = (tablero[byteActual] & ~mascara) | (valor << desplazamiento);
        return;
    }
    int bitsEnByte0= 8- desplazamiento;
    int bitsEnByte1 = 3- bitsEnByte0;
    unsigned char mascara0 = ((1<< bitsEnByte0)-1) << desplazamiento;
    unsigned char parte0= valor & ((1 << bitsEnByte0) -1);
    tablero[byteActual] = (tablero[byteActual] & ~mascara0) | (parte0 << desplazamiento);
    unsigned char mascara1 = (1 << bitsEnByte1)-1;
    unsigned char parte1 = (valor >> bitsEnByte0) & mascara1;
    tablero[byteActual +1] = (tablero[byteActual +1] & ~mascara1) | parte1;
}
void iniciarTablero(unsigned char *tablero, int filas, int columas){
    for (int f=0; f<filas; f++){
        for (int c=0; c< columas; c++){
            escribirFicha(tablero, columas, f,c,fichaAleatoria());
        }
    }
}
unsigned char* agregarFila(unsigned char *tablero, int* filas, int columnas, int posicion, int *bytesReservados){
    int filasViejas = *filas;
    int filasNuevas = filasViejas +1;
    int bytesNuevos= calcularbytes(filasNuevas, columnas);
    tablero= ampliarTablero(tablero, *bytesReservados, bytesNuevos);
    *bytesReservados = bytesNuevos;
    for (int f= filasViejas -1; f>=posicion; f--){
        for (int c=0; c< columnas; c++){
            unsigned char valor = obtenerFicha(tablero, columnas, f,c);
            escribirFicha(tablero,columnas, f+1,c,valor);
        }
    }
    for (int c=0; c<columnas; c++){
        escribirFicha(tablero, columnas, posicion,c,fichaAleatoria());
    }
    *filas = filasNuevas;
    return tablero;
}
unsigned char* eliminarFila(unsigned char *tablero, int* filas, int columnas, int posicion, int *bytesReservados){
    int filasViejas = *filas;
    int filasNuevas = filasViejas -1;
    for (int f = posicion +1; f<filasViejas; f++){
        for (int c=0; c< columnas; c++){
            unsigned char valor= obtenerFicha(tablero, columnas, f,c);
            escribirFicha(tablero, columnas, f-1,c,valor);
        }
    }
    for (int c=0; c< columnas; c++){
        escribirFicha(tablero, columnas, filasViejas -1,c,0);
    }
    *filas= filasNuevas;
    int bytesUsados= calcularbytes(filasNuevas,columnas);
    if (necesitaReducir(*bytesReservados,bytesUsados)){
        tablero = reducirTablero(tablero, *bytesReservados, bytesUsados);
    }
    return tablero;
}
unsigned char* agregarColumna(unsigned char *tablero, int filas, int* columnas, int posicion, int *bytesReservados){
    int columnasViejas = *columnas;
    int columnasNuevas =  columnasViejas +1;
    int bytesNuevos = calcularbytes(filas, columnasNuevas);
    tablero =ampliarTablero(tablero, *bytesReservados, bytesNuevos);
    *bytesReservados = bytesNuevos;
    for(int f=0; f<filas; f++){
        for(int c=columnasViejas-1; c>=posicion; c--){
            unsigned char valor = obtenerFicha(tablero, columnasViejas,f,c);
            escribirFicha(tablero, columnasNuevas,f, c+1, valor);
        }
    }
    for (int f=0; f<filas;f++){
        escribirFicha(tablero, columnasNuevas,f,posicion,fichaAleatoria());
    }
    *columnas=columnasNuevas;
    return tablero;
}
unsigned char* eliminarColumna(unsigned char *tablero, int filas, int *columnas, int posicion, int *bytesReservados){
    int columnasViejas= *columnas;
    int columnasNuevas= columnasViejas -1;
    for(int f=0; f< filas; f++){
        for (int c=posicion+1; c< columnasViejas; c++){
            unsigned char valor = obtenerFicha(tablero, columnasViejas,f,c);
            escribirFicha(tablero, columnasNuevas,f,c-1,valor);
        }
    }
    *columnas = columnasNuevas;
    int bytesUsados= calcularbytes(filas, columnasNuevas);
    if (necesitaReducir(*bytesReservados, bytesUsados)){
        tablero = reducirTablero(tablero, *bytesReservados, bytesUsados);
        *bytesReservados = bytesUsados;
    }
    return tablero;
}