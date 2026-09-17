#ifndef VISUAL_H
#define VISUAL_H

char obtenerSimbolo(unsigned char valor);
void mostrarTablero(unsigned char* tablero, int filas, int columnas);
void mostrarBits(unsigned char* tablero, int filas, int columnas);
void mostrarEstadisticas(int filas, int columnas, int eliminacionesUsuario, int fichasEliminadas, int combinacionesDetectadas, int puntuacion);
void mostrarMenu();
#endif // VISUAL_H