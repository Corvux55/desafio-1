#ifndef MEMORIA_H
#define MEMORIA_H

unsigned char* reservarTablero(int filas, int columnas);
void liberarTablero(unsigned char* tablero);
unsigned char* reducirTablero(unsigned char* tablero, int bytesViejos, int bytesNuevos);
unsigned char* ampliarTablero(unsigned char* tablero, int bytesViejos, int bytesNuevos);
int necesitaReducir(int bytesReservados, int bytesUsados);
#endif // MEMORIA_H
