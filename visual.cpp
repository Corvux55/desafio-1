#include <iostream>
#include "visual.h"
#include "tablero.h"
#include "util.h"

using namespace std;

char obtenerSimbolo(unsigned char valor) {
    if (valor == 1) return 'A';
    if (valor == 2) return 'B';
    if (valor == 3) return 'C';
    if (valor == 4) return 'D';
    if (valor == 5) return 'E';
    if (valor == 6) return 'F';
    return ' ';
}
void mostrarTablero(unsigned char* tablero, int filas, int columnas) {
    cout << "\n--- TABLERO ---" << endl;
    cout << "  ";
    for (int c = 0; c < columnas; c++) {
        cout << c << " ";
    }
    cout << endl;

    for (int f = 0; f < filas; f++) {
        cout << f << " ";
        for (int c = 0; c < columnas; c++) {
            unsigned char v = obtenerFicha(tablero, columnas, f, c);
            cout << obtenerSimbolo(v) << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void mostrarBits(unsigned char* tablero, int filas, int columnas) {
    int bytes = calcularbytes(filas, columnas);
    cout << "\n--- MEMORIA EN BITS bytes: " << bytes << " ---" << endl;
    for (int i = 0; i < bytes; i++) {
        cout << "Byte " << i << ": ";
        for (int b = 7; b >= 0; b--) {
            cout << ((tablero[i] >> b) & 1);
        }
        cout << endl;
    }
    cout << endl;
}

void mostrarMenu() {
    cout << "1. Eliminar ficha" << endl;
    cout << "2. Agregar fila" << endl;
    cout << "3. Eliminar fila" << endl;
    cout << "4. Agregar columna" << endl;
    cout << "5. Eliminar columna" << endl;
    cout << "6. Ver bits en memoria" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}