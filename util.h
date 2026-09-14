#ifndef UTIL_H
#define UTIL_H

void iniciarAleatorio();
unsigned char fichaAleatoria();
int dimensionesValidas(int filas, int columnas);
int coordenadasValidas(int fila, int columna, int filas, int columnas);
int calcularbytes(int filas, int columnas);
#endif // UTIL_H
