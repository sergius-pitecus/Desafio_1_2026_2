#ifndef FUNCIONES_JUEGO_H
#define FUNCIONES_JUEGO_H

bool comparar_fichas(unsigned char ** ptr_contenido, short int fila_1, short int fila_2, short int columna_1,
    short int columna_2, short int num_columnas);

short int buscar_arriba(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas);

short int buscar_abajo(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas, short int num_filas);

short int buscar_izquierda(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas);

short int buscar_derecha(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas);

void print_tablero(unsigned char ** ptr_contenido, short int num_columnas, short int num_filas);

short int buscar_combinaciones(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas);

void rellenar_huecos(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas);

void quitar_una_ficha(unsigned char ** ptr_contenido, short int num_columnas,short int fila,short int columna);

void mostrar_juego(unsigned char ** ptr_contenido, short int *ptr_filas,short int * ptr_columnas);

#endif