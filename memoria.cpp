#include "memoria.h"
#include "util.h"

unsigned char* reservarTablero(int filas, int columnas){
    int bytes = calcularbytes(filas, columnas);
    unsigned char* tablero= new unsigned char[bytes];
    if (tablero ==0){
        return 0;
    }
    for (int i=0; i < bytes; i++){
        tablero[i] =0;
    }
    return tablero;
}
void liberarTablero(unsigned char* tablero){
    if (tablero !=0){
    delete[] tablero;
    }
}
unsigned char* reducirTablero(unsigned char *tablero, int bytesViejos, int bytesNuevos){
    if (bytesNuevos >= bytesViejos){
        return tablero;
    }
    unsigned char* nuevo = new unsigned char[bytesNuevos];
    for (int i =0; i< bytesNuevos; i++){
        nuevo[i] = tablero[i];
    }
    delete[] tablero;
    return nuevo;
}
//recordar liberar eso
unsigned char* ampliarTablero(unsigned char *tablero, int bytesViejos, int bytesNuevos){
    if(bytesNuevos <= bytesViejos){
        return tablero;
    }
    unsigned char* nuevo = new unsigned char[bytesNuevos];
    for (int i=0; i< bytesViejos; i++){
        nuevo[i] = tablero[i];
    }
    for (int i = bytesViejos; i < bytesNuevos; i++){
        nuevo[i]=0;
    }
    delete[] tablero;
    return nuevo;
}
//tambien recordar liberar esto
int necesitaReducir(int bytesReservados, int bytesUsados){
    int limite = (bytesReservados * 65)/100;
    if (bytesUsados < limite){
        return 1;
    }
    return 0;
}