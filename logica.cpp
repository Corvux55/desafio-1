#include "logica.h"
#include "tablero.h"
#include "util.h"

int buscarYBorrarCombinaciones(unsigned char* tablero, int filas, int columnas, int* fichasEliminadas){
    int combinaciones = 0;

    unsigned char* borrar = new unsigned char[filas * columnas];
    for(int i = 0; i < filas * columnas; i++) borrar[i] = 0;
    // HORIZONTAL
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas - 2; c++) {
            unsigned char f1 = obtenerFicha(tablero, columnas, f, c);
            unsigned char f2 = obtenerFicha(tablero, columnas, f, c + 1);
            unsigned char f3 = obtenerFicha(tablero, columnas, f, c + 2);

            if (f1 >= 1 && f1 <= 6 && f1 == f2 && f2 == f3) {
                borrar[f * columnas + c] = 1;
                borrar[f * columnas + (c + 1)] = 1;
                borrar[f * columnas + (c + 2)] = 1;
                combinaciones++;
            }
        }
    }
    // VERTICAL
    for (int c = 0; c < columnas; c++) {
        for (int f = 0; f < filas - 2; f++) {
            unsigned char f1 = obtenerFicha(tablero, columnas, f, c);
            unsigned char f2 = obtenerFicha(tablero, columnas, f + 1, c);
            unsigned char f3 = obtenerFicha(tablero, columnas, f + 2, c);

            if (f1 >=1 && f1 == f2 && f2 == f3) {
                borrar[f * columnas + c] = 1;
                borrar[(f + 1) * columnas + c] = 1;
                borrar[(f + 2) * columnas + c] = 1;
                combinaciones++;
            }
        }
    }
    // Borrar filas
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (borrar[f * columnas + c] == 1) {
                escribirFicha(tablero, columnas, f, c, 0);
                (*fichasEliminadas)++;
            }
        }
    }

    delete[] borrar;
    return combinaciones;
}
void hacerCaerFichas(unsigned char* tablero, int filas, int columnas){
    for (int c = 0; c < columnas; c++) {
        // Gravedad: Bajar fichas
        //se separo por segmentos y recorre de abajo hacia arriba
        int fondo = filas -1;
        for (int f = filas -1; f>=0; f--){
            unsigned char valor = obtenerFicha(tablero, columnas,f,c);
            if (valor ==7){
                //es un obstaculo, no se mueve
                //el fondo es arriba del obstaculo
                fondo = f-1;
            }
            else if (valor >=1 && valor <=6){
                if (f != fondo){
                    escribirFicha(tablero, columnas, fondo, c, valor);
                    escribirFicha(tablero, columnas, f, c,0);
                }
                fondo --;
            }
        }
        // Rellenar espacios arriba con fichas nuevas
        for (int f = 0; f < filas; f++) {
            if (obtenerFicha(tablero, columnas, f, c) == 0) {
                escribirFicha(tablero, columnas, f, c, fichaAleatoria());
            }
        }
    }
}
int procesarCascadas(unsigned char* tablero, int filas, int columnas, int* combinacionesDetectadas, int* fichasEliminas) {
    int puntuacion =0;
    int nivel = 0;
    while (true) {
        int fichasAntes = *fichasEliminas;
        int encontradas = buscarYBorrarCombinaciones(tablero, filas, columnas,fichasEliminas);
        if(encontradas == 0){
            break;
        }
        *combinacionesDetectadas += encontradas;
        nivel++;
        int fichasEnEsteNivel = *fichasEliminas - fichasAntes;
        int puntosPorficha =0;
        if (nivel ==1){
            puntosPorficha = 10;
        }
        else if (nivel ==2){
            puntosPorficha = 20;
        }
        else{
            puntosPorficha =40;
        }
        puntuacion += fichasEnEsteNivel * puntosPorficha;
        if (fichasEnEsteNivel >=5){
            puntuacion +=50;
        }
        hacerCaerFichas(tablero, filas, columnas);
    }
    return puntuacion;
}