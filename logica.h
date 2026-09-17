#ifndef LOGICA_H
#define LOGICA_H

int buscarYBorrarCombinaciones(unsigned char* tablero, int filas, int columnas, int* fichasEliminadas);
void hacerCaerFichas(unsigned char* tablero, int filas, int columnas);
int procesarCascadas(unsigned char* tablero, int filas, int columnas, int* combinacionesDetectadas, int* fichasEliminas);
#endif // LOGICA_H