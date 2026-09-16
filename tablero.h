#ifndef TABLERO_H
#define TABLERO_H
void iniciarTablero(unsigned char* tablero, int filas, int columas);
unsigned char obtenerFicha(unsigned char* tablero, int columnas, int fila, int columna);
void escribirFicha(unsigned char* tablero, int columnas, int fila, int columna, unsigned char valor);
unsigned char* agregarFila(unsigned char* tablero, int* filas, int columnas, int posicion,  int* bytesReservados);
unsigned char* eliminarFila(unsigned char* tablero, int* filas, int columnas, int posicion,  int* bytesReservados);
unsigned char* agregarColumna(unsigned char* tablero, int filas, int* columnas, int posicion,  int* bytesReservados);
unsigned char* eliminarColumna(unsigned char* tablero, int filas, int* columnas, int posicion,  int* bytesReservados);
#endif // TABLERO_H
