#ifndef FUNCIONES_JUEGO_H
#define FUNCIONES_JUEGO_H

bool comparar_fichas(unsigned char ** ptr_contenido, unsigned short fila_1, unsigned short fila_2, unsigned short columna_1,
    unsigned short columna_2, unsigned short num_columnas);

unsigned short buscar_arriba(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas);

unsigned short buscar_abajo(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas, unsigned short num_filas);

unsigned short buscar_izquierda(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas);

unsigned short buscar_derecha(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas);

void print_tablero(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short num_filas);

void print_tablero_binario(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short num_filas);

unsigned short buscar_combinaciones(unsigned char ** ptr_contenido,unsigned short num_filas,unsigned short num_columnas, unsigned short * ptr_fichas_eliminadas);

void rellenar_huecos(unsigned char ** ptr_contenido,unsigned short num_filas, unsigned short num_columnas);

void quitar_una_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas,unsigned short fila,unsigned short columna);

void mostrar_juego(unsigned char ** ptr_contenido, unsigned short *ptr_filas,unsigned short * ptr_columnas,
    unsigned short *ptr_fichas_eliminadas, unsigned short * num_combinaciones_total, unsigned short num_eliminaciones,
    unsigned short * puntos, unsigned short eliminaciones_puntuales);

#endif