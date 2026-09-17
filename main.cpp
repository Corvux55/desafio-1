#include <iostream>
#include "util.h"
#include "memoria.h"
#include "tablero.h"
#include "visual.h"
#include "logica.h"

using namespace std;

int main() {
    iniciarAleatorio();

    int filas, columnas;
    cout << "Filas iniciales: ";
    cin >> filas;
    cout << "Columnas iniciales: ";
    cin >> columnas;

    int bytesReservados = calcularbytes(filas, columnas);
    unsigned char* tablero = reservarTablero(filas, columnas);

    iniciarTablero(tablero, filas, columnas);
    procesarCascadas(tablero, filas, columnas); // Limpiar tablero

    int opcion = -1;
    while (opcion != 0) {
        mostrarTablero(tablero, filas, columnas);
        mostrarMenu();
        cin >> opcion;

        if (opcion == 1) {
            int f, c;
            cout << "Fila: "; cin >> f;
            cout << "Columna: "; cin >> c;
            escribirFicha(tablero, columnas, f, c, 0); // Eliminar ficha
            hacerCaerFichas(tablero, filas, columnas);
            procesarCascadas(tablero, filas, columnas);
        }
        else if (opcion == 2) {
            int pos;
            cout << "Posicion fila agregar: "; cin >> pos;
            tablero = agregarFila(tablero, &filas, columnas, pos, &bytesReservados);
            procesarCascadas(tablero, filas, columnas);
        }
        else if (opcion == 3) {
            int pos;
            cout << "Posicion fila eliminar: "; cin >> pos;
            tablero = eliminarFila(tablero, &filas, columnas, pos, &bytesReservados);
            procesarCascadas(tablero, filas, columnas);
        }
        else if (opcion == 4) {
            int pos;
            cout << "Posicion columna agregar: "; cin >> pos;
            tablero = agregarColumna(tablero, filas, &columnas, pos, &bytesReservados);
            procesarCascadas(tablero, filas, columnas);
        }
        else if (opcion == 5) {
            int pos;
            cout << "Posicion columna eliminar: "; cin >> pos;
            tablero = eliminarColumna(tablero, filas, &columnas, pos, &bytesReservados);
            procesarCascadas(tablero, filas, columnas);
        }
        else if (opcion == 6) {
            mostrarBits(tablero, filas, columnas);
        }
    }

    liberarTablero(tablero);
    return 0;
}