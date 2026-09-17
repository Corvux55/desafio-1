#include "logica.h"
#include "tablero.h"
#include "util.h"

int buscarYBorrarCombinaciones(unsigned char* tablero, int filas, int columnas){
    int combinaciones = 0;

    unsigned char* borrar = new unsigned char[filas * columnas];
    for(int i = 0; i < filas * columnas; i++) borrar[i] = 0;
    // HORIZONTAL
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas - 2; c++) {
            unsigned char f1 = obtenerFicha(tablero, columnas, f, c);
            unsigned char f2 = obtenerFicha(tablero, columnas, f, c + 1);
            unsigned char f3 = obtenerFicha(tablero, columnas, f, c + 2);

            if (f1 != 0 && f1 == f2 && f2 == f3) {
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

            if (f1 != 0 && f1 == f2 && f2 == f3) {
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
            }
        }
    }

    delete[] borrar;
    return combinaciones;
}
void hacerCaerFichas(unsigned char* tablero, int filas, int columnas){
    for (int c = 0; c < columnas; c++) {
        // Gravedad: Bajar fichas
        for (int paso = 0; paso < filas; paso++) {
            for (int f = filas - 1; f > 0; f--) {
                if (obtenerFicha(tablero, columnas, f, c) == 0) {
                    unsigned char arriba = obtenerFicha(tablero, columnas, f - 1, c);
                    escribirFicha(tablero, columnas, f, c, arriba);
                    escribirFicha(tablero, columnas, f - 1, c, 0);
                }
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
void procesarCascadas(unsigned char* tablero, int filas, int columnas) {
    while (true) {
        int encontradas = buscarYBorrarCombinaciones(tablero, filas, columnas);
        if (encontradas == 0) {
            break;
        }
        hacerCaerFichas(tablero, filas, columnas);
    }
}